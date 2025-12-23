#!/usr/bin/env python3
"""Convert trainer input blocks into trdata JSON files.

Usage:
  python trdata/convert_trdata.py --input ___InputData/Trainers_InputSample.txt --output trdata/edited

Behavior:
- Reads trainer blocks separated by blank lines.
- Expects first non-empty line = Trainer Name (optional modifier in parens).
- Second non-empty line = comma- or pipe-separated Pokemon names (supports quoted multi-word names).
- Remaining lines are labeled fields: `Item:`, `Level:`, `Nature:`, `Ability:`, `Move 1:`, `Move 2:`, `Move 3:`, `Move 4:`
- Loads defaults from `trdata/original/<id>.json` when possible.
- Writes JSON files to the specified output directory named `<trainerId>.json`.
"""
import argparse
import json
import os
import re
import shlex
from pathlib import Path


def parse_list_value(line: str):
    line = line.strip()
    if not line:
        return []
    # Remove label if present
    if ':' in line:
        _, val = line.split(':', 1)
    else:
        val = line
    val = val.strip()
    # Common separators
    if ',' in val:
        parts = [p.strip() for p in val.split(',') if p.strip()]
    elif '|' in val:
        parts = [p.strip() for p in val.split('|') if p.strip()]
    elif ';' in val:
        parts = [p.strip() for p in val.split(';') if p.strip()]
    else:
        # fallback to shlex to allow quoted multi-word names; if shlex fails, split on whitespace
        try:
            parts = shlex.split(val)
        except ValueError:
            parts = [p for p in re.split(r'\s+', val) if p]
    return parts


def load_trainer_map(path: Path):
    mapping = {}
    if not path.exists():
        return mapping
    with path.open(encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            # Try common formats: "id\tname" or "id,name" or "name\tid"
            if '\t' in line:
                a, b = line.split('\t', 1)
            elif ',' in line:
                a, b = [p.strip() for p in line.split(',', 1)]
            else:
                parts = line.split()
                if parts[0].isdigit():
                    a = parts[0]
                    b = ' '.join(parts[1:])
                else:
                    a = None
                    b = line
            if a is None:
                continue
            # prefer mapping from name -> id
            try:
                key = b.strip()
                mapping[key.lower()] = int(a)
            except Exception:
                try:
                    mapping[a.strip().lower()] = int(b)
                except Exception:
                    pass
    return mapping


def find_trainer_id(trainers_map, original_dir: Path, trainer_name: str):
    # Try map first
    tid = trainers_map.get(trainer_name.lower())
    if tid is not None:
        return tid
    # Fallback: search original json files for matching readable.name
    for p in original_dir.glob('*.json'):
        try:
            data = json.loads(p.read_text(encoding='utf-8'))
            readable = data.get('readable', {})
            name = readable.get('name') or readable.get('trainer_name')
            if name and name.lower() == trainer_name.lower():
                return int(p.stem)
        except Exception:
            continue
    return None


def build_output_json(original_raw: dict, original_readable: dict, trainer_name: str, num_pokemon: int, modifier: str):
    # battle type mapping
    battle_type = 0
    double_flag = 0
    if modifier == '2x':
        battle_type = 1
        double_flag = 1
    elif modifier == '3x':
        battle_type = 2
        double_flag = 1
    elif modifier in ('Left', 'Right'):
        battle_type = 0
        double_flag = 1

    # AI bit mapping (inferred from originals):
    AI_BITS = {
        'Prioritize Effectiveness': 0x1,
        'Evaluate Attacks': 0x2,
        'Expert': 0x4,
        'Prioritize Status': 0x8,
        'Risky Attacks': 0x10,
        'Double Battle': 0x80,
        'Partner': 0x800,
        'Roaming Pokemon': 0x800,
        'Safari Zone': 0x800,
        'Catching Demo': 0x800,
        'Prioritize Damage': 0x800,
        'Prioritize Healing': 0x800,
        'Utilize Weather': 0x800,
        'Harassment': 0x800,
    }

    # Build AI values per spec:
    # - raw.ai = 15 for normal, 135 when Double Battle modifier is present
    # - readable.ai = 5 for normal, 135 when Double Battle modifier is present
    # Keep readable boolean flags (Partner/Double Battle/etc.) derived below.
    ai_raw = 135 if double_flag else 15
    readable_ai = 135 if double_flag else 5

    raw = {
        'template': original_raw.get('template', original_raw.get('Partner', 0)),
        'class': original_raw.get('class', 0),
        'battle_type_1': battle_type,
        'num_pokemon': num_pokemon,
        'item_1': 0,
        'item_2': 0,
        'item_3': 0,
        'item_4': 0,
        'ai': ai_raw,
        'heal': 0,
        'money': original_raw.get('money', 0),
        'reward_item': original_raw.get('reward_item', 0),
    }

    readable = {
        'template': raw['template'],
        'class': original_raw.get('class_name', original_raw.get('class', '')),
        'battle_type_1': 'Doubles' if battle_type == 1 else ('Triples' if battle_type == 2 else 'Singles'),
        'num_pokemon': num_pokemon,
        'item_1': 'None',
        'item_2': 'None',
        'item_3': 'None',
        'item_4': 'None',
        'ai': readable_ai,
        'heal': 0,
        'money': raw['money'],
        'reward_item': 'None' if raw['reward_item'] == 0 else raw['reward_item'],
        'class_id': raw['class'],
        # Prefer the trainer name from the original readable JSON when available.
        'name': original_readable.get('name') or original_readable.get('trainer_name') or trainer_name,
        'has_moves': 1,
        'has_items': 0,
        'Prioritize Effectiveness': 1,
        'Evaluate Attacks': 1,
        'Expert': 1,
        'Prioritize Status': 1,
        'Risky Attacks': 0,
        'Prioritize Damage': 0,
        'Partner': 1 if original_readable.get('Partner') else 0,
        'Double Battle': 1 if double_flag else 0,
        'Prioritize Healing': 0,
        'Utilize Weather': 0,
        'Harassment': 0,
        'Roaming Pokemon': 1 if original_readable.get('Roaming Pokemon') else 0,
        'Safari Zone': 1 if original_readable.get('Safari Zone') else 0,
        'Catching Demo': 1 if original_readable.get('Catching Demo') else 0,
    }

    return {'raw': raw, 'readable': readable}


def process_block(block_lines, trainers_map, original_dir: Path, out_dir: Path):
    lines = [l.strip() for l in block_lines if l.strip()]
    if not lines:
        return
    # Trainer name and optional modifier
    first = lines[0]
    m = re.match(r'^(.*?)(?:\s*\((2x|3x|Left|Right)\))?$', first)
    if not m:
        raise ValueError(f'Invalid trainer name line: {first}')
    trainer_name = m.group(1).strip()
    modifier = m.group(2) or ''

    # Pokemon names on second line
    if len(lines) < 2:
        raise ValueError(f'Block missing pokemon line for trainer {trainer_name}')
    pokemon_names = parse_list_value(lines[1])
    num_pokemon = len(pokemon_names)
    # Collect labeled fields
    fields = {}
    for ln in lines[2:]:
        if ':' in ln:
            label, _ = ln.split(':', 1)
            fields[label.strip()] = ln

    items = parse_list_value(fields.get('Item', '')) if 'Item' in fields else []
    levels = parse_list_value(fields.get('Level', '')) if 'Level' in fields else []
    natures = parse_list_value(fields.get('Nature', '')) if 'Nature' in fields else []
    abilities = parse_list_value(fields.get('Ability', '')) if 'Ability' in fields else []
    moves = []
    for i in range(1, 5):
        moves.append(parse_list_value(fields.get(f'Move {i}', '')))

    # Basic validation
    if items and len(items) != num_pokemon:
        raise ValueError(f'Item count {len(items)} != pokemon count {num_pokemon} for {trainer_name}')
    if levels and len(levels) != num_pokemon:
        raise ValueError(f'Level count {len(levels)} != pokemon count {num_pokemon} for {trainer_name}')
    if natures and len(natures) != num_pokemon:
        raise ValueError(f'Nature count {len(natures)} != pokemon count {num_pokemon} for {trainer_name}')
    if abilities and len(abilities) != num_pokemon:
        raise ValueError(f'Ability count {len(abilities)} != pokemon count {num_pokemon} for {trainer_name}')
    for i, mvlist in enumerate(moves, start=1):
        if mvlist and len(mvlist) != num_pokemon:
            raise ValueError(f'Move {i} count {len(mvlist)} != pokemon count {num_pokemon} for {trainer_name}')

    # Find trainer id
    tid = find_trainer_id(trainers_map, original_dir, trainer_name)
    tid_str = None
    if tid is None:
        # fallback: use sanitized trainer name as filename
        tid_str = re.sub(r"[^A-Za-z0-9_]+", '_', trainer_name.strip()).strip('_')
        print(f'Warning: trainer id not found for "{trainer_name}" — using filename "{tid_str}.json"')
        original_raw = {}
    else:
        original_file = original_dir / f'{tid}.json'
        original_raw = {}
        if original_file.exists():
            try:
                data = json.loads(original_file.read_text(encoding='utf-8'))
                original_raw = data.get('raw', {})
                original_readable = data.get('readable', {})
                # try to grab a class name for readable
                if 'readable' in data and 'class' in data['readable']:
                    original_raw['class_name'] = data['readable']['class']
                original_raw.setdefault('template', data.get('raw', {}).get('template', 0))
            except Exception:
                original_raw = {}
                original_readable = {}

    out_json = build_output_json(original_raw, original_readable if 'original_readable' in locals() else {}, trainer_name, num_pokemon, modifier)
    # Ensure the readable 'name' uses the original JSON's trainer name when available.
    if 'original_readable' in locals() and original_readable:
        out_json['readable']['name'] = original_readable.get('name') or original_readable.get('trainer_name') or trainer_name
    else:
        out_json['readable']['name'] = trainer_name
    out_dir.mkdir(parents=True, exist_ok=True)
    out_path = out_dir / (f'{tid}.json' if tid is not None else f'{tid_str}.json')
    out_path.write_text(json.dumps(out_json, ensure_ascii=False), encoding='utf-8')
    print(f'Wrote {out_path}')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--input', required=True)
    ap.add_argument('--output', required=True)
    ap.add_argument('--maps', default='___MAPS')
    ap.add_argument('--original', default='trdata/original')
    args = ap.parse_args()

    trainers_map = load_trainer_map(Path(args.maps) / 'Trainers.txt')
    original_dir = Path(args.original)
    out_dir = Path(args.output)

    text = Path(args.input).read_text(encoding='utf-8')
    # Split blocks by two or more newlines
    raw_blocks = re.split(r'\n\s*\n', text)
    for block in raw_blocks:
        lines = block.splitlines()
        if any(l.strip() for l in lines):
            process_block(lines, trainers_map, original_dir, out_dir)


if __name__ == '__main__':
    main()
