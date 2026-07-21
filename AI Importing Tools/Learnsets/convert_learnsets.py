import os
import re
import json
import argparse


def normalize_name(s: str) -> str:
    s = s.upper()
    s = re.sub(r"[^A-Z0-9]", "", s)
    return s


def format_readable_move_name(name: str) -> str:
    # Keep MoveId canonical spacing/hyphenation/casing structure; only uppercase letters.
    return name.upper()


def load_move_map(path: str):
    move_ids = {}
    move_names = {}
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
            norm = normalize_name(name)
            move_ids[norm] = mid
            move_names[norm] = name
    return move_ids, move_names


def load_compatibility_map(path: str):
    cmap = {}
    if not os.path.exists(path):
        return cmap

    with open(path, encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line or "->" not in line:
                continue
            left, right = [part.strip() for part in line.split("->", maxsplit=1)]
            if not left or not right:
                continue
            cmap[left] = right
    return cmap


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


def autofix_sample_move_names(sample_path, move_ids, move_names):
    with open(sample_path, encoding="utf-8") as f:
        lines = f.readlines()

    fixed_lines = []
    changes = []
    unknown_moves = []

    for line in lines:
        m = re.match(r"^(\s*)(\d+)(\s+)(.+?)\s*$", line)
        if not m:
            fixed_lines.append(line)
            continue

        prefix = m.group(1)
        level = m.group(2)
        sep = m.group(3)
        move_name = m.group(4)
        norm = normalize_name(move_name)

        if norm not in move_ids:
            unknown_moves.append(move_name)
            fixed_lines.append(line)
            continue

        canonical = move_names[norm]
        if move_name != canonical:
            changes.append((move_name, canonical))
            fixed_lines.append(f"{prefix}{level}{sep}{canonical}\n")
        else:
            fixed_lines.append(line)

    if changes:
        with open(sample_path, "w", encoding="utf-8") as f:
            f.writelines(fixed_lines)

    return changes, unknown_moves


def validate_move_name_format(blocks, move_ids, move_names, compatibility_map):
    unknown_moves = []
    formatting_mismatches = []

    for pokemon_name, moves in blocks:
        for _, move_name in moves:
            norm = normalize_name(move_name)
            if norm not in move_ids:
                unknown_moves.append((pokemon_name, move_name))
                continue

            canonical = move_names[norm]
            if move_name != canonical:
                suggested = compatibility_map.get(move_name, canonical)
                formatting_mismatches.append((pokemon_name, move_name, suggested, canonical))

    if not unknown_moves and not formatting_mismatches:
        return True

    print("\nMove name validation failed against MoveId.txt")

    if unknown_moves:
        print("\nUnknown moves (not found in MoveId.txt):")
        for pokemon_name, move_name in sorted(set(unknown_moves)):
            print(f"  - {pokemon_name}: '{move_name}'")

    if formatting_mismatches:
        print("\nFormatting mismatches (must match MoveId.txt spelling/spacing/hyphenation):")
        for pokemon_name, move_name, suggested, canonical in sorted(set(formatting_mismatches)):
            extra = ""
            if suggested != canonical:
                extra = f" (compatibility note suggests '{suggested}')"
            print(f"  - {pokemon_name}: '{move_name}' -> '{canonical}'{extra}")

    return False


def build_learnset(pokemon_name, moves, pmap, move_ids, move_names):
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
        mid = move_ids.get(mn_norm)
        if mid is None:
            print(f"Warning: move '{mname}' not found in MoveId.txt for Pokémon '{pokemon_name}'")
            continue
        canonical_name = move_names[mn_norm]
        # raw should only include the move id and level learned
        raw[f"move_id_{idx}"] = mid
        raw[f"lvl_learned_{idx}"] = lvl

        # readable keeps human names, level, and an index mapping to the move id
        readable[f"move_id_{idx}"] = format_readable_move_name(canonical_name)
        readable[f"lvl_learned_{idx}"] = lvl
        readable[f"move_id_{idx}_index"] = mid
        idx += 1

    # readable includes the pokemon index
    readable["index"] = pid

    return {"raw": raw, "readable": readable}


def main():
    parser = argparse.ArgumentParser(
        description="Convert learnset source data into per-Pokemon JSON files."
    )
    parser.add_argument(
        "--autofix-sample",
        action="store_true",
        help="Rewrite SampleData.txt move names to canonical MoveId.txt formatting before validation.",
    )
    args = parser.parse_args()

    root = os.path.dirname(os.path.abspath(__file__))
    move_file = os.path.join(root, "MoveId.txt")
    poke_file = os.path.join(root, "PokemonID.txt")
    sample_file = os.path.join(root, "SampleData.txt")
    compatibility_file = os.path.join(root, "ComptabilityNotes.txt")
    out_dir = os.path.join(root, "Final_Learnsets")
    os.makedirs(out_dir, exist_ok=True)

    move_ids, move_names = load_move_map(move_file)
    compatibility_map = load_compatibility_map(compatibility_file)
    pmap = load_pokemon_map(poke_file)

    if args.autofix_sample:
        changes, unknown_moves = autofix_sample_move_names(sample_file, move_ids, move_names)
        print(f"Autofix: updated {len(changes)} move-name entries in SampleData.txt")
        if unknown_moves:
            print("Autofix warning: unknown move names were left unchanged:")
            for move_name in sorted(set(unknown_moves)):
                print(f"  - {move_name}")

    print("Sample file path:", sample_file)
    print("Exists:", os.path.exists(sample_file))
    try:
        print("Size:", os.path.getsize(sample_file))
    except Exception as e:
        print("Size error:", e)

    blocks = parse_sample(sample_file)

    print(f"Loaded {len(move_ids)} moves, {len(pmap)} pokemon, parsed {len(blocks)} blocks")
    if blocks:
        print("First block name:", blocks[0][0])
    else:
        with open(sample_file, encoding="utf-8") as f:
            c = f.read()
        print("SampleData snippet repr:", repr(c[:200]))

    if not validate_move_name_format(blocks, move_ids, move_names, compatibility_map):
        raise SystemExit(1)

    written = 0
    for pname, moves in blocks:
        ls = build_learnset(pname, moves, pmap, move_ids, move_names)
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
