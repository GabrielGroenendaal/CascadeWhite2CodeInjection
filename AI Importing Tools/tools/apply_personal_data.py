import re
import json
from pathlib import Path

maps_dir = Path('Personal/_maps')
input_file = Path('Personal/Personal_InputData.txt')
original_dir = Path('Personal/original')
out_dir = Path('Personal/edited')
report_file = Path('tools/personal_apply_report.txt')

# load PokemonID map (name -> id)
pid_map = {}
pid_path = maps_dir / 'PokemonID.txt'
if pid_path.exists():
    for ln in pid_path.read_text(encoding='utf-8', errors='replace').splitlines():
        ln = ln.strip()
        if not ln:
            continue
        parts = re.split(r'\s+|\t', ln, maxsplit=1)
        if len(parts) >= 2 and parts[0].isdigit():
            pid_map[parts[1].strip().lower()] = int(parts[0])

# load abilities map (name -> id)
abilities_map = {}
ab_path = maps_dir / 'Abilities.txt'
if ab_path.exists():
    for ln in ab_path.read_text(encoding='utf-8', errors='replace').splitlines():
        ln = ln.strip()
        if not ln:
            continue
        if '\t' in ln:
            a,b = ln.split('\t',1)
        else:
            parts = re.split(r'\s{2,}|\s+', ln)
            if len(parts) >= 2:
                a,b = parts[0], ' '.join(parts[1:])
            else:
                continue
        # some files are 'id name' or 'name id'
        if a.isdigit():
            abilities_map[b.strip().lower()] = int(a)
        elif b.isdigit():
            abilities_map[a.strip().lower()] = int(b)
        else:
            # fallback: try split by last token
            parts2 = ln.rsplit(None, 1)
            if len(parts2) == 2 and parts2[1].isdigit():
                abilities_map[parts2[0].strip().lower()] = int(parts2[1])

# parse Personal_InputData.txt
text = input_file.read_text(encoding='utf-8', errors='replace')
blocks = re.split(r'\n\s*\n', text)
parsed = {}
for block in blocks:
    lines = [l.strip() for l in block.splitlines() if l.strip()]
    if not lines:
        continue
    # first line is Pokemon name (may include form)
    name = lines[0].strip()
    # subsequent lines may include 'Stats:', 'Typing:', 'Abilities:' etc
    info = {'stats': {}, 'types': [], 'abilities': []}
    for ln in lines[1:]:
        if ln.lower().startswith('stats'):
            # e.g. Stats: HP 60 / Atk 62 / Def 63 / SpA 80 / SpD 80 / Spe 60
            m = re.findall(r"([A-Za-z]+)\s*(\d+)", ln)
            for k,v in m:
                key = k.lower()
                info['stats'][key] = int(v)
        elif ln.lower().startswith('typing') or ln.lower().startswith('type'):
            # Type: Water / Ground
            parts = re.split(r'[:\t]', ln, 1)
            val = parts[1] if len(parts) > 1 else ''
            types = [p.strip() for p in re.split(r'/|,', val) if p.strip()]
            info['types'] = types
        elif ln.lower().startswith('abilities'):
            parts = ln.split(':',1)
            if len(parts) > 1:
                abil_parts = [p.strip() for p in re.split(r',|/', parts[1]) if p.strip()]
                info['abilities'] = abil_parts
        else:
            # try to detect key: value
            if ':' in ln:
                k,v = ln.split(':',1)
                if k.strip().lower() in ('abilities','type','typing','stats'):
                    # handled above
                    pass
    parsed[name] = info

# helper normalization
def norm_name(n):
    if not n:
        return ''
    s = n.strip()
    # remove leading index markers like '#1'
    s = re.sub(r'^#\d+\s*', '', s)
    # remove leading 'Type' labels
    s = re.sub(r'^Type\s*', '', s, flags=re.I)
    s = s.replace('\u2019', "'")
    s = s.replace('\u2013','-').replace('\u2014','-')
    s = s.strip()
    return s.lower()

out_dir.mkdir(parents=True, exist_ok=True)
report_lines = []
count_updated = 0
count_skipped = 0
missing = []

for pname, info in parsed.items():
    key = norm_name(pname)
    pid = pid_map.get(key)
    # try variants
    if pid is None:
        variants = []
        variants.append(key.replace(' ', '-'))
        variants.append(key.replace(' ', ''))
        variants.append(re.sub(r"[^a-z0-9\-]", '', key))
        # swap form order (e.g., 'castform sunny' -> 'castform-sunny')
        variants.append(key.replace(' ', '-').upper().lower())
        for v in variants:
            if v in pid_map:
                pid = pid_map[v]
                break
    # last resort: try substring match in pid_map keys
    if pid is None:
        for k in pid_map.keys():
            if key in k:
                pid = pid_map[k]
                break
    if pid is None:
        missing.append(pname)
        continue
    orig_file = original_dir / f'{pid}.json'
    if not orig_file.exists():
        missing.append(f'{pname} (id {pid})')
        continue
    try:
        data = json.loads(orig_file.read_text(encoding='utf-8'))
    except Exception as e:
        report_lines.append(f'ERROR reading {orig_file}: {e}')
        continue
    raw = data.get('raw', {})
    readable = data.get('readable', {})
    changed = []
    # apply stats (raw likely stores stats under hp, atk, def, spa, spd, spe or 'base_stats')
    # try common keys
    stats_map = {
        'hp': ['hp','base_hp'], 'atk': ['atk','base_atk','attack'], 'def': ['def','base_def','defense'],
        'spa': ['spa','base_spa','spatk','sp_atk','sp_atk'], 'spd': ['spd','base_spd','spdef','sp_def','sp_def'], 'spe': ['spe','base_spe','speed']
    }
    for sname, svals in info.get('stats', {}).items():
        sname_l = sname.lower()
        # match first known key that exists or set base_stats dict
        applied = False
        for canonical, keys in stats_map.items():
            if sname_l.startswith(canonical) or sname_l in ('hp','atk','def','spa','spd','spe','attack','defense','speed'):
                for k in keys:
                    if k in raw:
                        if raw.get(k) != svals:
                            raw[k] = svals
                            changed.append(f'stat {k} -> {svals}')
                        applied = True
                        break
                if applied:
                    break
        if not applied:
            # try nested base_stats
            if 'base_stats' in raw and isinstance(raw['base_stats'], dict):
                kk = sname_l
                if kk in raw['base_stats']:
                    if raw['base_stats'][kk] != svals:
                        raw['base_stats'][kk] = svals
                        changed.append(f'base_stats.{kk} -> {svals}')
                        applied = True
            if not applied:
                raw.setdefault('base_stats', {})[sname_l] = svals
                changed.append(f'base_stats.{sname_l} -> {svals}')
    # apply types
    types = info.get('types', [])
    if types:
        # store in readable maybe 'type1','type2' or raw['types']
        t1 = types[0] if len(types) >=1 else ''
        t2 = types[1] if len(types) >=2 else ''
        prev = (raw.get('type1') or readable.get('type1') or raw.get('types') or readable.get('types'))
        # normalize
        if raw.get('type1') != t1:
            raw['type1'] = t1
            changed.append(f'type1 -> {t1}')
        if t2:
            if raw.get('type2') != t2:
                raw['type2'] = t2
                changed.append(f'type2 -> {t2}')
    # apply abilities
    abils = info.get('abilities', [])
    if abils:
        # map names to ids when possible
        abil_ids = []
        for a in abils:
            aid = abilities_map.get(a.lower())
            if aid is None:
                # try trim
                aid = abilities_map.get(a.split()[0].lower())
            abil_ids.append(aid if aid is not None else a)
        # store in raw['abilities'] or raw['ability']
        if raw.get('abilities') != abil_ids:
            raw['abilities'] = abil_ids
            changed.append(f'abilities -> {abil_ids}')
    if changed:
        count_updated += 1
        data['raw'] = raw
        data['readable'] = readable
        out_file = out_dir / f'{pid}.json'
        out_file.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding='utf-8')
        report_lines.append(f'Updated {pid} ({pname}): ' + '; '.join(changed))
    else:
        count_skipped += 1

report_lines.append('')
report_lines.append(f'Updated: {count_updated}, Skipped(no changes): {count_skipped}, Missing: {len(missing)}')
if missing:
    report_lines.append('Missing entries:')
    report_lines += missing

report_file.write_text('\n'.join(report_lines), encoding='utf-8')
print('Done. Wrote edits to', out_dir, 'and report to', report_file)
