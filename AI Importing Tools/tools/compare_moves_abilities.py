import re
from pathlib import Path

calc_path = Path('trpok/CalcOutput.txt')
input_path = Path('trpok/Trainers_InputData.txt')

def norm(s):
    if s is None:
        return ''
    s = s.strip()
    s = s.replace('\u2019', "'")
    s = s.replace('\u2013','-')
    s = s.replace('\u2014','-')
    return re.sub(r"[^A-Za-z0-9 '\-]", '', s).lower()

# parse input blocks
input_text = input_path.read_text(encoding='utf-8', errors='replace')
blocks = re.split(r'\n\s*\n', input_text)
input_data = {}
for block in blocks:
    lines = [l.rstrip() for l in block.splitlines() if l.strip()]
    if not lines:
        continue
    first = lines[0]
    m = re.match(r'^(.*?)(?:\s*\((2x|3x|Left|Right)\))?$', first)
    trainer = m.group(1).strip() if m else first.strip()
    # collect lists
    fields = {}
    for ln in lines[2:]:
        if ':' in ln:
            label, val = ln.split(':',1)
            fields[label.strip()] = val.strip()
    pokes = []
    # second line poke names
    if len(lines) >= 2:
        sec = lines[1]
        if ':' in sec:
            sec = sec.split(':',1)[1]
        parts = [p.strip() for p in re.split(r'\t|\s{2,}|,|\|', sec) if p.strip()]
        pokes = parts
    # parse abilities and moves per index
    abilities = []
    moves = []
    # parse ability line
    abil_list = []
    if 'Ability' in fields:
        abil_list = [p.strip() for p in re.split(r'\t|,|\|', fields['Ability']) if p.strip()]
    move_lists = []
    for i in range(1,5):
        key = f'Move {i}'
        if key in fields:
            move_parts = [p.strip() for p in re.split(r'\t|,|\|', fields[key]) if p.strip()]
        else:
            move_parts = []
        move_lists.append(move_parts)
    # for each pokemon index, ability is abil_list[idx] if present, moves are move_lists per move stacked
    for idx in range(len(pokes)):
        a = abil_list[idx] if idx < len(abil_list) else ''
        abilities.append(norm(a))
        mlist = []
        for mvlist in move_lists:
            if idx < len(mvlist):
                mname = mvlist[idx]
                if mname and mname != '-----':
                    mlist.append(norm(mname))
        moves.append([m for m in mlist if m])
    input_data[trainer] = {'pokes': pokes, 'abilities': abilities, 'moves': moves}

# parse calc output
calc_lines = calc_path.read_text(encoding='utf-8', errors='replace').splitlines()
pat = re.compile(r'^(?P<name>.+?)\s+(?P<id>\d+)\s+\((Singles|Doubles|Triples)\)')
calc_data = {}
cur = None
cur_abilities = []
cur_moves = []
cur_pokes = []
for ln in calc_lines:
    m = pat.match(ln)
    if m:
        if cur:
            calc_data[cur] = {'pokes': cur_pokes, 'abilities': cur_abilities, 'moves': cur_moves}
        cur = m.group('name').strip()
        cur_pokes = []
        cur_abilities = []
        cur_moves = []
        continue
    if cur:
        if ln.strip().startswith('---'):
            if cur:
                calc_data[cur] = {'pokes': cur_pokes, 'abilities': cur_abilities, 'moves': cur_moves}
            cur = None
            cur_pokes = []
            cur_abilities = []
            cur_moves = []
            continue
        if not ln.strip():
            continue
        # ignore headers
        if ln.strip().startswith('>') or ln.strip().startswith('-'):
            continue
        parts = [p for p in re.split(r'\s{2,}|\t', ln.strip()) if p.strip()]
        if not parts:
            continue
        sp = parts[0]
        # find ability: try parts[3] or parts[4]
        ability = ''
        moves_part = ''
        if len(parts) >= 4:
            ability = parts[3]
        # moves often last part
        if len(parts) >= 5:
            moves_part = parts[-1]
        # split moves by comma
        movs = [norm(mv) for mv in re.split(r',', moves_part) if mv.strip() and mv.strip() != '-----']
        cur_pokes.append(sp)
        cur_abilities.append(norm(ability))
        cur_moves.append(movs)

# comparison
common = set(input_data.keys()) & set(calc_data.keys())
print(f'Common trainers: {len(common)}')
mismatch_report = []
for t in sorted(common):
    inp = input_data[t]
    cal = calc_data[t]
    minlen = min(len(inp['pokes']), len(cal['pokes']))
    for i in range(minlen):
        ia = inp['abilities'][i] if i < len(inp['abilities']) else ''
        ca = cal['abilities'][i] if i < len(cal['abilities']) else ''
        if ia != ca:
            mismatch_report.append((t, i, 'ability', inp['pokes'][i] if i < len(inp['pokes']) else '', ia, ca))
        im = set(inp['moves'][i]) if i < len(inp['moves']) else set()
        cm = set(cal['moves'][i]) if i < len(cal['moves']) else set()
        if im != cm:
            mismatch_report.append((t, i, 'moves', inp['pokes'][i] if i < len(inp['pokes']) else '', sorted(list(im - cm)) , sorted(list(cm - im))))

print(f'Total mismatches: {len(mismatch_report)}')
for row in mismatch_report[:200]:
    if row[2] == 'ability':
        print(f"{row[0]} [{row[1]}]: ability input='{row[4]}' calc='{row[5]}'")
    else:
        print(f"{row[0]} [{row[1]}]: moves only-in-input={row[4]} only-in-calc={row[5]}")

# write CSV of mismatches
out = Path('tools/moves_abilities_mismatches.csv')
with out.open('w', encoding='utf-8') as f:
    f.write('trainer,index,type,subject,input,calc\n')
    for row in mismatch_report:
        if row[2] == 'ability':
            f.write(f'"{row[0]}",{row[1]},ability,"{row[3]}","{row[4]}","{row[5]}"\n')
        else:
            f.write(f'"{row[0]}",{row[1]},moves,"{row[3]}","{row[4]}","{row[5]}"\n')
print('Wrote tools/moves_abilities_mismatches.csv')
