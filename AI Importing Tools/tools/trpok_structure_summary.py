#!/usr/bin/env python3
"""Summarize structural differences between trpok/original and trpok/Edited_All into CSV.

Outputs `tools/trpok_structure_summary.csv` with per-file counts and samples.
"""
import json
from pathlib import Path
import csv


def summarize(orig_dir: Path, edited_dir: Path, out_csv: Path):
    orig_files = {p.stem: p for p in orig_dir.glob('*.json')}
    edited_files = {p.stem: p for p in edited_dir.glob('*.json')}
    common = sorted(set(orig_files.keys()) & set(edited_files.keys()))

    rows = []
    for stem in common:
        o = json.loads(orig_files[stem].read_text(encoding='utf-8'))
        e = json.loads(edited_files[stem].read_text(encoding='utf-8'))
        for section in ('raw', 'readable'):
            osec = o.get(section, {})
            esec = e.get(section, {})
            okeys = set(osec.keys())
            ekeys = set(esec.keys())
            only_orig = sorted(list(okeys - ekeys))
            only_edited = sorted(list(ekeys - okeys))
            common_keys = sorted(list(okeys & ekeys))
            type_mismatches = []
            for k in common_keys:
                ot = type(osec.get(k)).__name__
                et = type(esec.get(k)).__name__
                if ot != et:
                    type_mismatches.append(f"{k}:{ot}->{et}")

            rows.append({
                'file': stem + '.json',
                'section': section,
                'only_in_original_count': len(only_orig),
                'only_in_edited_count': len(only_edited),
                'type_mismatch_count': len(type_mismatches),
                'only_in_original_sample': '|'.join(only_orig[:5]),
                'only_in_edited_sample': '|'.join(only_edited[:5]),
                'type_mismatch_sample': '|'.join(type_mismatches[:5]),
            })

    out_csv.parent.mkdir(parents=True, exist_ok=True)
    with out_csv.open('w', encoding='utf-8', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=['file','section','only_in_original_count','only_in_edited_count','type_mismatch_count','only_in_original_sample','only_in_edited_sample','type_mismatch_sample'])
        writer.writeheader()
        for r in rows:
            # align field name: type_mismatch_count
            r2 = r.copy()
            r2['type_mismatch_count'] = r2.pop('type_mismatch_count', r2.get('type_mismatch_count', ''))
            writer.writerow(r2)

    print(f'Wrote {out_csv}')


if __name__ == '__main__':
    summarize(Path('trpok/original'), Path('trpok/Edited_All'), Path('tools/trpok_structure_summary.csv'))
