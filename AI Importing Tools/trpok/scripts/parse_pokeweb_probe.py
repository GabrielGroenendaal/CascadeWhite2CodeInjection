import re
import sys
from pathlib import Path

probe = Path('trpok/pokeweb_probe_682_3_255.txt')
if not probe.exists():
    print('Probe file not found:', probe)
    sys.exit(1)

if len(sys.argv) > 1:
    nature = sys.argv[1]
else:
    print('Usage: parse_pokeweb_probe.py <Nature>')
    sys.exit(1)

text = None
for enc in ('utf-8', 'utf-16', 'cp1252', 'latin-1'):
    try:
        text = probe.read_text(encoding=enc)
        break
    except Exception:
        continue
if text is None:
    print('Failed to read probe file with common encodings')
    sys.exit(2)
key = nature = sys.argv[1].strip()
if not key:
    print('Empty nature')
    sys.exit(1)

# regex to find patterns like '254 IVs: Quiet' (case-insensitive)
pat = re.compile(r"(?i)\b(\d{1,3})\s+IVs:\s*" + re.escape(key) + r"\b")
matches = [int(m) for m in pat.findall(text)]
if matches:
    print(f'Found matches for nature "{nature}":', sorted(matches))
    print('Highest IV:', max(matches))
else:
    print(f'No exact matches for nature "{nature}" found.')
    # list distinct natures appearing in 'IVs: <Nature>' occurrences to help debug
    all_pat = re.compile(r"\b(\d{1,3})\s+IVs:\s*([A-Za-z ]+)\b")
    found = [m.group(2).strip() for m in all_pat.finditer(text)]
    uniq = sorted(set(found), key=lambda s: (len(s), s))
    print('Distinct natures seen (sample):', uniq[:30])
