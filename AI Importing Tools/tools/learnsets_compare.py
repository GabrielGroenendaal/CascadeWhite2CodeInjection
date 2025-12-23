import os
import json
from pathlib import Path

root = Path(__file__).resolve().parents[1] / "Learnsets"
orig_dir = root / "Original"
final_dir = root / "Final_Learnsets"
out_dir = Path(__file__).resolve().parents[0]

def load_json(p):
    try:
        with open(p, encoding='utf-8') as f:
            return json.load(f)
    except Exception as e:
        return None

orig_files = {p.name for p in orig_dir.glob('*.json')}
final_files = {p.name for p in final_dir.glob('*.json')}

common = sorted(orig_files & final_files)
only_orig = sorted(orig_files - final_files)
only_final = sorted(final_files - orig_files)

summary_lines = []
diff_lines = []

summary_lines.append('file,only_in_original_count,only_in_final_count,only_in_original_sample,only_in_final_sample')

for name in common:
    orig = load_json(orig_dir / name)
    fin = load_json(final_dir / name)
    if orig is None or fin is None:
        diff_lines.append(f"{name}: failed to load JSON (orig_ok={orig is not None}, final_ok={fin is not None})")
        summary_lines.append(f"{name},-1,-1,ERROR,ERROR")
        continue
    # compare top-level keys
    o_keys = set(orig.keys())
    f_keys = set(fin.keys())
    only_o_top = sorted(o_keys - f_keys)
    only_f_top = sorted(f_keys - o_keys)
    # compare nested keys for raw/readable if present
    nested_only_o = []
    nested_only_f = []
    for k in ('raw','readable'):
        if k in orig and k in fin:
            o_sub = set(orig[k].keys())
            f_sub = set(fin[k].keys())
            only_o = sorted(o_sub - f_sub)
            only_f = sorted(f_sub - o_sub)
            if only_o:
                nested_only_o.extend([f"{k}.{x}" for x in only_o])
            if only_f:
                nested_only_f.extend([f"{k}.{x}" for x in only_f])
    only_o_all = only_o_top + nested_only_o
    only_f_all = only_f_top + nested_only_f
    count_o = len(only_o_all)
    count_f = len(only_f_all)
    sample_o = '|'.join(only_o_all[:5]) if only_o_all else ''
    sample_f = '|'.join(only_f_all[:5]) if only_f_all else ''
    summary_lines.append(f"{name},{count_o},{count_f},{sample_o},{sample_f}")
    if count_o or count_f:
        diff_lines.append(f"=== {name} ===")
        if only_o_top:
            diff_lines.append("Only in original (top-level): " + ", ".join(only_o_top))
        if only_f_top:
            diff_lines.append("Only in final (top-level): " + ", ".join(only_f_top))
        if nested_only_o:
            diff_lines.append("Only in original (nested): " + ", ".join(nested_only_o))
        if nested_only_f:
            diff_lines.append("Only in final (nested): " + ", ".join(nested_only_f))
        diff_lines.append("")

# add files only in one side
if only_orig:
    diff_lines.append('Files only in Original:')
    diff_lines.extend(only_orig)
    diff_lines.append('')
if only_final:
    diff_lines.append('Files only in Final_Learnsets:')
    diff_lines.extend(only_final)
    diff_lines.append('')

# write outputs
with open(out_dir / 'learnsets_summary.csv', 'w', encoding='utf-8') as f:
    f.write('\n'.join(summary_lines))
with open(out_dir / 'learnsets_diff.txt', 'w', encoding='utf-8') as f:
    f.write('\n'.join(diff_lines))

print('Wrote tools/learnsets_summary.csv and tools/learnsets_diff.txt')
