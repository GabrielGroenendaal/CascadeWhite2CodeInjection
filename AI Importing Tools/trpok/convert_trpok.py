#!/usr/bin/env python3
"""Convert trainer Pokemon input blocks into `trpok` JSON files.

Usage:
  python trpok/convert_trpok.py --input trpok/Trainers_InputData.txt --output trpok/Edited --maps trpok/_maps --original trpok/original

Notes:
- Requires maps in `--maps`: `Trainers.txt`, `PokemonID.txt`, `MoveId.txt`, `Items.txt`, `Abilities.txt`, `AI_Abilities_MAP.txt`.
- Attempts to fetch IV->nature mappings from `http://localhost:9292/trainers/<trainerId>/pokemon/<index>/natures/<iv>` (falls back to defaults if server unavailable).
"""
import argparse
import json
import re
import shlex
import os
from pathlib import Path
from typing import Optional

try:
    import requests
except Exception:
    requests = None


def parse_list_value(line: str):
    line = line.strip()
    if not line:
        return []
    # If value contains a label (e.g. "Move 1\tSecret Power\tAstonish..."),
    # remove the leading token before parsing only when the line begins with a known label.
    val = line
    if ':' in line:
        _, val = line.split(':', 1)
    elif '\t' in line:
        left = line.lstrip()
        # only strip the first column when the left-most token looks like a field label
        label_pattern = r'^(Item|Level|Nature|Ability|Move\s*\d+|Move)\b'
        if re.match(label_pattern, left, re.I):
            parts0 = [p for p in line.split('\t') if p.strip()]
            if len(parts0) > 1:
                parts0 = parts0[1:]
            val = '\t'.join(parts0)
        else:
            val = line
    val = val.strip()
    if not val:
        return []
    if '\t' in val:
        parts = [p.strip() for p in val.split('\t') if p.strip()]
    elif ',' in val:
        parts = [p.strip() for p in val.split(',') if p.strip()]
    elif '|' in val:
        parts = [p.strip() for p in val.split('|') if p.strip()]
    elif ';' in val:
        parts = [p.strip() for p in val.split(';') if p.strip()]
    else:
        try:
            parts = shlex.split(val)
        except ValueError:
            parts = [p for p in re.split(r'\s+', val) if p]
    return parts


def load_map(path: Path):
    mapping = {}
    if not path.exists():
        return mapping
    for line in path.read_text(encoding='utf-8').splitlines():
        line = line.strip()
        if not line:
            continue
        # split on tabs or commas first
        if '\t' in line:
            parts = [p.strip() for p in line.split('\t') if p.strip()]
        elif ',' in line:
            parts = [p.strip() for p in line.split(',') if p.strip()]
        else:
            parts = [p for p in re.split(r'\s{2,}|\s+', line) if p]
        if not parts:
            continue
        # find numeric token (id)
        id_token = None
        name_tokens = []
        for tok in parts:
            if tok.isdigit():
                id_token = tok
            else:
                name_tokens.append(tok)
        if id_token is None:
            # try last token numeric
            if parts[-1].isdigit():
                id_token = parts[-1]
                name_tokens = parts[:-1]
            elif parts[0].isdigit():
                id_token = parts[0]
                name_tokens = parts[1:]
            else:
                continue
        name = ' '.join(name_tokens).strip()
        if not name:
            continue
        try:
            mapping[name.lower()] = int(id_token)
        except Exception:
            continue
    return mapping


def load_ai_abilities_map(path: Path):
    table = {}
    if not path.exists():
        return table
    for line in path.read_text(encoding='utf-8').splitlines():
        line = line.strip()
        if not line:
            continue
        # Prefer splitting on tabs (file is tab-separated). If no tabs present,
        # fall back to splitting on two-or-more spaces so multi-word ability
        # names (e.g. "Flash Fire") are preserved.
        if '\t' in line:
            parts = [p.strip() for p in line.split('\t') if p.strip()]
        else:
            parts = [p for p in re.split(r'\s{2,}', line) if p and p.strip()]
        if not parts:
            continue
        if parts[0].isdigit() and len(parts) >= 2:
            name = parts[1].strip()
            abilities = [p.strip() for p in parts[2:] if p.strip()]
            table[name.lower()] = abilities
    return table


def find_trainer_id(trainers_map, original_dir: Path, trainer_name: str):
    tid = trainers_map.get(trainer_name.lower())
    if tid is not None:
        return tid
    for p in original_dir.glob('*.json'):
        try:
            data = json.loads(p.read_text(encoding='utf-8'))
            readable = data.get('readable', {})
            name = readable.get('name')
            if name and name.lower() == trainer_name.lower():
                return int(p.stem)
        except Exception:
            continue
    return None


_iv_cache = {}
_pokeweb_base = os.environ.get('POKEWEB_BASE_URL', 'http://localhost:9292')


def _parse_int_from_text(text: str) -> Optional[int]:
    # Try to find an explicit JSON-friendly int first
    try:
        j = json.loads(text)
        if isinstance(j, int):
            return int(j)
        if isinstance(j, dict) and 'iv' in j and isinstance(j['iv'], int):
            return int(j['iv'])
    except Exception:
        pass
    # Fallback: find first small integer in body
    m = re.search(r'\b(\d{1,3})\b', text)
    if m:
        try:
            return int(m.group(1))
        except Exception:
            return None
    return None


def fetch_iv_for_nature(trainer_id, poke_index, nature):
    """Attempt to query pokeweb for the IV value for a given `nature`.

    Behavior:
    - Uses `POKEWEB_BASE_URL` env var or `http://localhost:9292` by default.
    - Tries these endpoints (in order) until one returns an integer:
      1. /trainers/{trainer_id}/pokemon/{poke_index}/natures/{nature}
      2. /natures/{nature}
      3. /api/natures/{nature}
    - Accepts JSON responses (int or {{"iv": N}}) or HTML/text containing an integer.
    - Caches lookups per `nature` to avoid repeated requests.
    - On any error or if `requests` is unavailable, returns 255.
    """
    # Cache key must include trainer and poke index since mappings differ per trainer/poke
    key = f"{trainer_id}:{poke_index}:{str(nature).strip().lower()}"
    if not key:
        return 255
    if key in _iv_cache:
        return _iv_cache[key]

    # allow urllib fallback if `requests` is not installed; continue

    base = _pokeweb_base.rstrip('/')
    # Developer/testing convenience: if a local probe file exists, use it
    probe_file = Path(f'trpok/pokeweb_probe_{trainer_id}_{poke_index}_255.txt')
    if probe_file.exists():
        data = None
        for enc in ('utf-8', 'utf-16', 'cp1252', 'latin-1'):
            try:
                data = probe_file.read_text(encoding=enc)
                break
            except Exception:
                continue
        if data is None:
            data = probe_file.read_bytes().decode('latin-1', errors='replace')
        try:
            all_pat = re.compile(r"\b(\d{1,3})\s+IVs:\s*([A-Za-z ]+)\b", re.I)
            matches = [int(m.group(1)) for m in all_pat.finditer(data) if m.group(2).strip().lower() == str(nature).strip().lower()]
            if matches:
                iv = max(matches)
                _iv_cache[key] = iv
                try:
                    Path('trpok').mkdir(parents=True, exist_ok=True)
                    with open(Path('trpok/ivs_resolved.txt'), 'a', encoding='utf-8') as f:
                        f.write(f"{trainer_id},{poke_index},{nature},{iv}\n")
                except Exception:
                    pass
                return iv
        except Exception:
            pass
    # Prefer trainer-specific endpoints. Try both 1- and 0-based indices and
    # both the simple 255 route and the /natures/ route.
    try:
        idx_one = int(poke_index) + 1
    except Exception:
        idx_one = poke_index
    endpoints = [
        f"{base}/trainers/{trainer_id}/{idx_one}/255",
        f"{base}/trainers/{trainer_id}/{poke_index}/255",
        f"{base}/trainers/{trainer_id}/{idx_one}/natures/255",
        f"{base}/trainers/{trainer_id}/{poke_index}/natures/255",
        f"{base}/trainers/{trainer_id}/pokemon/{poke_index}/natures/{str(nature).strip().lower()}",
        f"{base}/natures/{str(nature).strip().lower()}",
        f"{base}/api/natures/{str(nature).strip().lower()}",
    ]

    for url in endpoints:
        try:
            if requests is not None:
                resp = requests.get(url, timeout=3)
                if resp.status_code != 200:
                    continue
            else:
                # fallback to urllib when requests is unavailable
                import urllib.request
                import urllib.error
                import json as _json
                try:
                    with urllib.request.urlopen(url, timeout=3) as r:
                        content_bytes = r.read()
                        status = r.getcode()
                except Exception:
                    continue
                class _SimpleResp:
                    def __init__(self, status, content_bytes):
                        self.status_code = status
                        self.content = content_bytes
                        try:
                            self.text = content_bytes.decode('utf-8')
                        except Exception:
                            try:
                                self.text = content_bytes.decode('cp1252')
                            except Exception:
                                self.text = content_bytes.decode('latin-1', errors='replace')
                    def json(self):
                        return _json.loads(self.text)
                resp = _SimpleResp(status, content_bytes)
            # Try JSON first
            try:
                j = resp.json()
            except Exception:
                j = None

            # If we have a JSON mapping, try to find the nature -> iv or iv -> nature
            if isinstance(j, dict):
                # direct mapping: nature -> iv
                for kname, v in j.items():
                    try:
                        if str(kname).strip().lower() == str(nature).strip().lower():
                            iv = int(v)
                            iv = max(0, min(255, iv))
                            _iv_cache[key] = iv
                            # record resolved IV
                            Path('trpok/ivs_resolved.txt').write_text(f"{trainer_id},{poke_index},{nature},{iv}\n", encoding='utf-8', append=False) if False else None
                            return iv
                    except Exception:
                        continue
                # inverse mapping: iv -> nature
                for kname, v in j.items():
                    try:
                        if str(v).strip().lower() == str(nature).strip().lower() and str(kname).isdigit():
                            iv = int(kname)
                            iv = max(0, min(255, iv))
                            _iv_cache[key] = iv
                            return iv
                    except Exception:
                        continue

            # Fallback: decode bytes with multiple encodings and search for textual 'IVs: <Nature>' entries.
            body = None
            for enc in ('utf-8', 'utf-16', 'cp1252', 'latin-1'):
                try:
                    body = resp.content.decode(enc)
                    break
                except Exception:
                    continue
            if body is None:
                body = resp.text

            try:
                # Find all 'N IVs: Nature' occurrences and select those matching the requested nature.
                all_pat = re.compile(r"\b(\d{1,3})\s+IVs:\s*([A-Za-z ]+)\b", re.I)
                matches = []
                for m in all_pat.finditer(body):
                    ivnum = int(m.group(1))
                    nat = m.group(2).strip()
                    if nat.lower() == str(nature).strip().lower():
                        matches.append(ivnum)
                if matches:
                    iv = max(matches)
                    iv = max(0, min(255, iv))
                    _iv_cache[key] = iv
                    # append resolved entry to file
                    try:
                        Path('trpok').mkdir(parents=True, exist_ok=True)
                        with open(Path('trpok/ivs_resolved.txt'), 'a', encoding='utf-8') as f:
                            f.write(f"{trainer_id},{poke_index},{nature},{iv}\n")
                    except Exception:
                        pass
                    return iv
            except Exception:
                pass

            ivval = _parse_int_from_text(body if body is not None else resp.text)
            if ivval is not None:
                iv = max(0, min(255, int(ivval)))
                _iv_cache[key] = iv
                return iv
        except Exception:
            continue

    # last resort
    _iv_cache[key] = 255
    return 255


def process_block(block_lines, maps_dir: Path, original_dir: Path, out_dir: Path):
    lines = [l.strip() for l in block_lines if l.strip()]
    if not lines:
        return
    first = lines[0]
    m = re.match(r'^(.*?)(?:\s*\((2x|3x|Left|Right)\))?$', first)
    if not m:
        raise ValueError(f'Invalid trainer name line: {first}')
    trainer_name = m.group(1).strip()
    modifier = m.group(2) or ''

    if len(lines) < 2:
        raise ValueError(f'Missing pokemon line for trainer {trainer_name}')
    pokemon_names = parse_list_value(lines[1])
    num_pokemon = len(pokemon_names)

    fields = {}
    for ln in lines[2:]:
        if '\t' in ln:
            label, val = ln.split('\t', 1)
            fields[label.strip()] = val.strip()
        elif ':' in ln:
            label, val = ln.split(':', 1)
            fields[label.strip()] = val.strip()
        else:
            # unrecognized line format; skip
            continue

    items = parse_list_value(fields.get('Item', '')) if 'Item' in fields else []
    levels = parse_list_value(fields.get('Level', '')) if 'Level' in fields else []
    natures = parse_list_value(fields.get('Nature', '')) if 'Nature' in fields else []
    abilities = parse_list_value(fields.get('Ability', '')) if 'Ability' in fields else []
    moves = []
    for i in range(1, 5):
        moves.append(parse_list_value(fields.get(f'Move {i}', '')))

    # load maps
    trainers_map = load_map(maps_dir / 'Trainers.txt')
    pokemon_map = load_map(maps_dir / 'PokemonID.txt')
    move_map = load_map(maps_dir / 'MoveId.txt')
    items_map = load_map(maps_dir / 'Items.txt')
    abilities_map = load_map(maps_dir / 'Abilities.txt')
    ai_abilities = load_ai_abilities_map(maps_dir / 'AI_Abilities_MAP.txt')

    tid = find_trainer_id(trainers_map, original_dir, trainer_name)
    tid_str = None
    if tid is None:
        tid_str = re.sub(r"[^A-Za-z0-9_]+", '_', trainer_name.strip()).strip('_')
        print(f'Warning: trainer id not found for "{trainer_name}" — using filename "{tid_str}.json"')

    original_raw = {}
    original_readable = {}
    if tid is not None:
        original_file = original_dir / f'{tid}.json'
        if original_file.exists():
            try:
                data = json.loads(original_file.read_text(encoding='utf-8'))
                original_raw = data.get('raw', {})
                original_readable = data.get('readable', {})
            except Exception:
                original_raw = {}
                original_readable = {}

    out_raw = {}
    out_readable = {}

    for idx, pname in enumerate(pokemon_names):
        i = idx
        species_id = pokemon_map.get(pname.lower())
        if species_id is None:
            print(f'Error: unknown Pokemon "{pname}" for trainer "{trainer_name}"')
            species_id = 0

        # item
        item_id = 0
        if items:
            item_name = items[idx] if idx < len(items) else ''
            item_id = items_map.get(item_name.lower(), 0)

        # level
        level = 1
        if levels and idx < len(levels):
            try:
                lvl = int(levels[idx])
                level = max(1, min(100, lvl))
            except Exception:
                level = 1

        # nature -> iv
        # For this conversion pass we ignore nature lookups and set IVs to 255 for every Pokemon.
        nature = natures[idx] if idx < len(natures) else 'Varies'
        iv = 255

        # ability -> find index in AI map
        ability_name = abilities[idx] if idx < len(abilities) else ''
        abil_index = 1
        if ability_name:
            # first check ability exists
            if ability_name.lower() not in abilities_map:
                print(f'Error: ability "{ability_name}" not found in Abilities map for trainer {trainer_name}')
            # find index in ai_abilities row
            row = ai_abilities.get(pname.lower(), [])
            found_index = None
            for k, a in enumerate(row, start=1):
                if a and a.lower() == ability_name.lower():
                    found_index = k
                    break
            if found_index is None:
                # fallback: choose 1
                abil_index = 1
            else:
                abil_index = found_index

        ability_raw = abil_index * 16

        # moves
        move_ids = [0, 0, 0, 0]
        for mv_i in range(4):
            mvlist = moves[mv_i]
            if mvlist and idx < len(mvlist):
                mvname = mvlist[idx]
                mid = move_map.get(mvname.lower())
                if mid is None:
                    print(f'Warning: move "{mvname}" not found for {pname} (trainer {trainer_name})')
                    mid = 0
                move_ids[mv_i] = mid

        # write raw/readable fields
        out_raw[f'ivs_{i}'] = iv
        out_raw[f'ability_{i}'] = ability_raw
        out_raw[f'level_{i}'] = level
        out_raw[f'padding_{i}'] = 0
        out_raw[f'species_id_{i}'] = species_id
        out_raw[f'form_{i}'] = 0
        out_raw[f'item_id_{i}'] = item_id
        out_raw[f'move_1_{i}'] = move_ids[0]
        out_raw[f'move_2_{i}'] = move_ids[1]
        out_raw[f'move_3_{i}'] = move_ids[2]
        out_raw[f'move_4_{i}'] = move_ids[3]

        out_readable[f'ivs_{i}'] = iv
        out_readable[f'ability_{i}'] = abil_index
        out_readable[f'level_{i}'] = level
        out_readable[f'padding_{i}'] = 0
        out_readable[f'species_id_{i}'] = pname
        out_readable[f'form_{i}'] = 0
        # find readable item name from map (reverse lookup)
        item_name_read = None
        for k, v in items_map.items():
            if v == item_id:
                item_name_read = k
                break
        out_readable[f'item_id_{i}'] = item_name_read.title() if item_name_read else 'None'
        # moves readable
        for mv_i in range(4):
            mid = move_ids[mv_i]
            move_name_read = None
            for k, v in move_map.items():
                if v == mid:
                    move_name_read = k
                    break
            out_readable[f'move_{mv_i+1}_{i}'] = move_name_read.upper() if move_name_read else 'None'

        out_readable[f'gender_{i}'] = 'Default'

    out_readable['count'] = num_pokemon
    out_readable['template'] = original_readable.get('template', 0) if original_readable else original_raw.get('template', 0)

    out_dir.mkdir(parents=True, exist_ok=True)
    fname = f'{tid}.json' if tid is not None else f'{tid_str}.json'
    out_path = out_dir / fname
    out_data = {'raw': out_raw, 'readable': out_readable}
    out_path.write_text(json.dumps(out_data, ensure_ascii=False), encoding='utf-8')
    print(f'Wrote {out_path}')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--input', required=True)
    ap.add_argument('--output', required=True)
    ap.add_argument('--maps', default='trpok/_maps')
    ap.add_argument('--original', default='trpok/original')
    args = ap.parse_args()

    maps_dir = Path(args.maps)
    original_dir = Path(args.original)
    out_dir = Path(args.output)

    text = Path(args.input).read_text(encoding='utf-8')
    raw_blocks = re.split(r'\n\s*\n', text)
    for block in raw_blocks:
        lines = block.splitlines()
        if any(l.strip() for l in lines):
            process_block(lines, maps_dir, original_dir, out_dir)


if __name__ == '__main__':
    main()
