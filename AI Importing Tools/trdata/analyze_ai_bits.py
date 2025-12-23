#!/usr/bin/env python3
"""Analyze trdata/original JSON files to infer which bits in `raw.ai` map to readable AI flags."""
import json
from pathlib import Path


def load_all(orig_dir: Path):
    items = []
    for p in orig_dir.glob('*.json'):
        try:
            data = json.loads(p.read_text(encoding='utf-8'))
            raw = data.get('raw', {})
            readable = data.get('readable', {})
            ai = raw.get('ai')
            if ai is None:
                continue
            items.append((p.name, ai, readable))
        except Exception:
            continue
    return items


def infer_bits(items):
    # collect all boolean/int flags in readable
    flag_names = set()
    for _, ai, readable in items:
        for k, v in readable.items():
            if isinstance(v, int) and k not in ('ai', 'money', 'num_pokemon', 'class_id'):
                flag_names.add(k)
    flag_names = sorted(flag_names)

    # evaluate candidate bits up to 2^12
    maxbit = 12
    candidates = [1 << i for i in range(maxbit)]

    mapping = {}
    for flag in flag_names:
        best = []
        for b in candidates:
            matches = 0
            total = 0
            for _, ai, readable in items:
                if flag in readable and isinstance(readable[flag], int):
                    total += 1
                    want = 1 if readable[flag] else 0
                    has = 1 if (ai & b) else 0
                    if has == want:
                        matches += 1
            if total == 0:
                score = 0
            else:
                score = matches / total
            best.append((score, b))
        best.sort(reverse=True)
        mapping[flag] = best[:3]

    return mapping


def main():
    orig = Path('trdata/original')
    items = load_all(orig)
    print(f'Loaded {len(items)} trainer files from {orig}')
    mapping = infer_bits(items)
    for flag, best in mapping.items():
        print(f'Flag: {flag}')
        for score, b in best:
            print(f'  bit {b:>4} (0x{b:X}) match={score:.3f}')


if __name__ == '__main__':
    main()
