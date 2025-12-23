import os
import re
import json


def normalize_name(s: str) -> str:
    s = s.upper()
    s = re.sub(r"[^A-Z0-9]", "", s)
    return s


def load_move_map(path: str):
    moves = {}
    with open(path, encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            m = re.match(r"^(\d+)\s+(.+)$", line)
            if not m:
                continue
            mid = int(m.group(1))
            name = m.group(2).strip()
            moves[normalize_name(name)] = mid
    return moves


def load_pokemon_map(path: str):
    pmap = {}
    with open(path, encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            m = re.match(r"^(\d+)\s+(.+)$", line)
            if not m:
                continue
            pid = int(m.group(1))
            name = m.group(2).strip()
            pmap[normalize_name(name)] = pid
    return pmap


def parse_sample(path: str):
    with open(path, encoding="utf-8") as f:
        content = f.read()
    blocks = re.split(r"\n\s*\n+", content.strip())
    result = []
    for block in blocks:
        lines = [ln.strip() for ln in block.splitlines() if ln.strip()]
        if not lines:
            continue
        name = lines[0]
        moves = []
        for ln in lines[1:]:
            parts = re.split(r"\s+", ln, maxsplit=1)
            if not parts:
                continue
            lvl = parts[0]
            try:
                lvl_i = int(lvl)
            except ValueError:
                # if line doesn't start with level, skip
                continue
            move_name = parts[1].strip() if len(parts) > 1 else ""
            moves.append((lvl_i, move_name))
        result.append((name, moves))
    return result


def build_learnset(pokemon_name, moves, pmap, mmap):
    pnorm = normalize_name(pokemon_name)
    if pnorm not in pmap:
        print(f"Warning: Pokémon '{pokemon_name}' not found in PokemonID.txt")
        return None
    pid = pmap[pnorm]

    raw = {}
    readable = {}
    idx = 0
    for lvl, mname in moves:
        mn_norm = normalize_name(mname)
        mid = mmap.get(mn_norm)
        if mid is None:
            print(f"Warning: move '{mname}' not found in MoveId.txt for Pokémon '{pokemon_name}'")
            continue
        # raw should only include the move id and level learned
        raw[f"move_id_{idx}"] = mid
        raw[f"lvl_learned_{idx}"] = lvl

        # readable keeps human names, level, and an index mapping to the move id
        readable[f"move_id_{idx}"] = mname.upper()
        readable[f"lvl_learned_{idx}"] = lvl
        readable[f"move_id_{idx}_index"] = mid
        idx += 1

    # readable includes the pokemon index
    readable["index"] = pid

    return {"raw": raw, "readable": readable}


def main():
    root = os.path.dirname(os.path.abspath(__file__))
    move_file = os.path.join(root, "MoveId.txt")
    poke_file = os.path.join(root, "PokemonID.txt")
    sample_file = os.path.join(root, "SampleData.txt")
    out_dir = os.path.join(root, "Final_Learnsets")
    os.makedirs(out_dir, exist_ok=True)

    mmap = load_move_map(move_file)
    pmap = load_pokemon_map(poke_file)
    print("Sample file path:", sample_file)
    print("Exists:", os.path.exists(sample_file))
    try:
        print("Size:", os.path.getsize(sample_file))
    except Exception as e:
        print("Size error:", e)

    blocks = parse_sample(sample_file)

    print(f"Loaded {len(mmap)} moves, {len(pmap)} pokemon, parsed {len(blocks)} blocks")
    if blocks:
        print("First block name:", blocks[0][0])
    else:
        with open(sample_file, encoding="utf-8") as f:
            c = f.read()
        print("SampleData snippet repr:", repr(c[:200]))

    written = 0
    for pname, moves in blocks:
        ls = build_learnset(pname, moves, pmap, mmap)
        if ls is None:
            continue
        pid = ls["readable"]["index"]
        out_path = os.path.join(out_dir, f"{pid}.json")
        with open(out_path, "w", encoding="utf-8") as f:
            json.dump(ls, f, ensure_ascii=False)
        written += 1
    print(f"Wrote {written} learnset files to {out_dir}")


if __name__ == "__main__":
    main()
