#!/usr/bin/env python3
"""Compare JSON structures between trpok/original and trpok/Edited_All.

Writes a plain text report listing files with missing/extra keys and type mismatches.
"""
import json
from pathlib import Path
import argparse


def compare_files(orig_path: Path, edited_path: Path):
    try:
        o = json.loads(orig_path.read_text(encoding='utf-8'))
    except Exception as e:
        return f'ERROR reading original {orig_path}: {e}\n'
    try:
        e = json.loads(edited_path.read_text(encoding='utf-8'))
    except Exception as ex:
        return f'ERROR reading edited {edited_path}: {ex}\n'

    out_lines = []
    for section in ('raw', 'readable'):
        osec = o.get(section, {})
        esec = e.get(section, {})
        okeys = set(osec.keys())
        ekeys = set(esec.keys())
        only_orig = sorted(list(okeys - ekeys))
        only_edited = sorted(list(ekeys - okeys))
        if only_orig or only_edited:
            out_lines.append(f'-- Section: {section}')
            if only_orig:
                out_lines.append('  Only in original: ' + ', '.join(only_orig))
            if only_edited:
                out_lines.append('  Only in edited: ' + ', '.join(only_edited))

        # type mismatches for keys present in both
        common = sorted(list(okeys & ekeys))
        type_mismatches = []
        for k in common:
            ot = type(osec.get(k)).__name__
            et = type(esec.get(k)).__name__
            if ot != et:
                type_mismatches.append((k, ot, et))
        if type_mismatches:
            out_lines.append(f'-- Section: {section} type mismatches:')
            for k, ot, et in type_mismatches:
                out_lines.append(f'  {k}: original={ot} edited={et}')

    if not out_lines:
        return 'OK: structures match\n'
    return '\n'.join(out_lines) + '\n'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--orig', required=True)
    ap.add_argument('--edited', required=True)
    ap.add_argument('--out', required=True)
    args = ap.parse_args()

    orig_dir = Path(args.orig)
    edited_dir = Path(args.edited)
    report = []
    # gather common file stems
    orig_files = {p.stem: p for p in orig_dir.glob('*.json')}
    edited_files = {p.stem: p for p in edited_dir.glob('*.json')}
    common = sorted(set(orig_files.keys()) & set(edited_files.keys()))
    only_orig = sorted(set(orig_files.keys()) - set(edited_files.keys()))
    only_edited = sorted(set(edited_files.keys()) - set(orig_files.keys()))

    report.append(f'Common files: {len(common)}')
    report.append(f'Only in original: {len(only_orig)}')
    report.append(f'Only in edited: {len(only_edited)}')
    report.append('')

    for stem in common:
        orig_path = orig_files[stem]
        edited_path = edited_files[stem]
        report.append(f'File: {stem}.json')
        report.append(compare_files(orig_path, edited_path))

    # write report
    outp = Path(args.out)
    outp.parent.mkdir(parents=True, exist_ok=True)
    outp.write_text('\n'.join(report), encoding='utf-8')
    print(f'Wrote {outp}')


if __name__ == '__main__':
    main()
