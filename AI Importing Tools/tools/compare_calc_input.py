import re
from pathlib import Path

calc_path = Path('trpok/CalcOutput.txt')
input_path = Path('trpok/Trainers_InputData.txt')

calc_text = calc_path.read_text(encoding='utf-8', errors='replace')
input_text = input_path.read_text(encoding='utf-8', errors='replace')

# Parse calc: find header lines like 'Name 123 (Singles) (None)'
calc_lines = calc_text.splitlines()
calc_trainers = {}
pat = re.compile(r'^(?P<name>.+?)\s+(?P<id>\d+)\s+\((Singles|Doubles|Triples)\)')
cur = None
cur_pokes = []
for ln in calc_lines:
    m = pat.match(ln)
    if m:
        if cur:
            calc_trainers[cur] = cur_pokes
        cur = m.group('name').strip()
        cur_pokes = []
        continue
    if cur:
        # stop at delimiter '---'
        if ln.strip().startswith('---'):
            if cur:
                calc_trainers[cur] = cur_pokes
            cur = None
            cur_pokes = []
            continue
        # skip separators and section headers
        if not ln.strip():
            continue
        if ln.strip().startswith('---') or ln.strip().startswith('>>>') or ln.strip().startswith('---'):
            continue
        # species lines usually start with species name
        parts = re.split(r'\s{2,}|\t', ln.strip())
        if parts:
            sp = parts[0].strip()
            # ignore lines like '-----------------'
            if re.match(r'^-+$', sp):
                continue
            # exclude lines that are headers (e.g., 'Route 20')
            if sp.lower().startswith(('route','pokedex','----------------','>>>>>>>>')):
                continue
            # sometimes species lines start with an indent then species
            # collect first word or first two words if capitalized mid
            if sp:
                cur_pokes.append(sp)

# Parse input: split into blocks
blocks = re.split(r'\n\s*\n', input_text)
input_trainers = {}
for block in blocks:
    lines = [l.strip() for l in block.splitlines() if l.strip()]
    if not lines:
        continue
    # trainer name is first line
    first = lines[0]
    m = re.match(r'^(.*?)(?:\s*\((2x|3x|Left|Right)\))?$', first)
    tname = m.group(1).strip() if m else first.strip()
    # pokemon names usually on second line
    pokes = []
    if len(lines) >= 2:
        sec = lines[1]
        # remove leading label if present
        if ':' in sec:
            sec = sec.split(':',1)[1]
        # split by tab or multiple spaces or commas
        parts = [p.strip() for p in re.split(r'\t|\s{2,}|,|\|', sec) if p.strip()]
        pokes = parts
    input_trainers[tname] = pokes

# Compare sets
calc_set = set(calc_trainers.keys())
input_set = set(input_trainers.keys())
only_in_calc = sorted(calc_set - input_set)
only_in_input = sorted(input_set - calc_set)

print('Summary:')
print(f'  Trainers in calc: {len(calc_set)}')
print(f'  Trainers in input: {len(input_set)}')
print(f'  Only in calc: {len(only_in_calc)}')
print(f'  Only in input: {len(only_in_input)}')

if only_in_calc:
    print('\nTrainers only in CalcOutput (sample 20):')
    for n in only_in_calc[:20]:
        print('  ', n)
if only_in_input:
    print('\nTrainers only in Input (sample 20):')
    for n in only_in_input[:20]:
        print('  ', n)

# For common trainers, compare pokemon lists length and names
print('\nPer-trainer differences (count or species mismatches):')
count_diff = 0
species_diff = 0
for name in sorted(calc_set & input_set):
    calc_p = calc_trainers.get(name, [])
    inp_p = input_trainers.get(name, [])
    if len(calc_p) != len(inp_p):
        print(f'- {name}: calc has {len(calc_p)} pokemon, input has {len(inp_p)}')
        count_diff += 1
    else:
        # compare names (startswith) to be tolerant
        mismatches = []
        for a,b in zip(calc_p, inp_p):
            if not a.lower().startswith(b.lower()):
                mismatches.append((a,b))
        if mismatches:
            print(f'- {name}: species mismatches:')
            for a,b in mismatches[:5]:
                print(f'    calc: "{a}"  input: "{b}"')
            species_diff += 1

print(f'\nTotals: {count_diff} count mismatches, {species_diff} species mismatches')
