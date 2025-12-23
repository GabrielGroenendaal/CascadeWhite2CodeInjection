import importlib.util
from pathlib import Path
spec = importlib.util.spec_from_file_location('mod', r'c:/Users/gabeg/Documents/ROMhacks/____MyNewRomhack/____GitHub_CascadeWhite/AI Importing Tools/trpok/convert_trpok.py')
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)
mp = Path(r'c:/Users/gabeg/Documents/ROMhacks/____MyNewRomhack/____GitHub_CascadeWhite/AI Importing Tools/trpok/_maps/AI_Abilities_MAP.txt')
table = mod.load_ai_abilities_map(mp)
print('typhlosion' in table)
print('typhlosion ->', table.get('typhlosion'))
# print a small sample near typhlosion
for key in sorted(k for k in table.keys() if k.startswith('ty')):
    print(key, '=>', table[key])
