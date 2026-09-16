#!/usr/bin/env python3
"""
Compiles every .cpp source in __ComplexCodeInjection into a .elf, mirroring
the arm-none-eabi-g++ invocations in ../commandprompts.txt, then converts
each .elf into a loadable .dll (RPM0 module) via CTRMap's rpm.cli.RPMTool,
resolving external symbols against the source's relevant ESDB.

- Top-level sources (A4_AbilityChanges.cpp, A8_ImportedAbilities.cpp, ...)
  compile to ______Output/<stem>.elf, and convert to ______Output/patches/<stem>.dll.
- abilities/*.cpp compile to ______Output/<ability id>.elf, where the
  id is looked up from the AbilID enum in definitions/A_Structs.h (matched by
  converting the filename to SCREAMING_SNAKE_CASE and comparing against the
  ABILnnn_<NAME> enum entries), per abilities/__filename_to_patchname.txt, and
  convert to ______Output/patches/abilities/<ability id>.dll (see dll_output_path).
- Each source's ESDB is picked by ESDB_FOR_SOURCE (keyed by source stem),
  falling back to DEFAULT_ESDB for everything not listed there (A4 and all
  of abilities/*.cpp).

All printed/executed commands use paths relative to PARENT
(___BasicCodeInjectionForSharing) and run with that as the working
directory, matching the convention in ../commandprompts.txt - so this
script (and the commands it prints) work the same whether you run it from
inside __ComplexCodeInjection or from the ___BasicCodeInjectionForSharing
root.

Usage (from either __ComplexCodeInjection or ___BasicCodeInjectionForSharing):
    python __ComplexCodeInjection/build.py                    # resolve ids, compile, and convert everything
    python __ComplexCodeInjection/build.py --dry-run          # only resolve ids / print commands, do nothing
    python __ComplexCodeInjection/build.py --elf-only         # compile only, skip the .elf -> .dll step
    python __ComplexCodeInjection/build.py --group patches    # only the 6 top-level sources, skip all abilities
    python __ComplexCodeInjection/build.py --group abilities  # only abilities/*.cpp
    python __ComplexCodeInjection/build.py field               # substring match against stem -> D2_FieldOverlays
    python __ComplexCodeInjection/build.py Trace Guts          # only these sources (stem substring match)
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PARENT = ROOT.parent  # ___BasicCodeInjectionForSharing
GCC = Path(
    r"C:\Users\gabeg\Documents\ROMhacks\____MyNewRomhack\_____GithubCheckoutMarch"
    r"\arm-gnu-toolchain-13.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-g++.exe"
)
OUTPUT_DIR = ROOT / "______Output"
FLAGS = ["-r", "-mthumb", "-mlong-calls", "-march=armv5t", "-Os"]

# .elf intermediates stay flat in OUTPUT_DIR. .dll outputs are split into two
# subfolders of "patches" (mirroring PW2Code's own Assets/patches/ convention
# for this kind of output):
# - Ability modules -> patches/abilities/<id>.dll
# - Top-level branch-injected sources -> patches/<stem>.dll
DLL_LIB_DIR = OUTPUT_DIR / "patches" / "abilities"
DLL_PATCH_DIR = OUTPUT_DIR / "patches"

ABILITIES_DIR = ROOT / "abilities"
ABILID_HEADER = ROOT / "definitions" / "A_Structs.h"

TOP_LEVEL_EXCLUDE = {"build.py"}

CTRMAP_JAR = PARENT.parent / "___IDBS" / "Overlay142_new" / "CTRMap.jar"

# ESDB to resolve each source's external symbols against, keyed by source
# filename stem. Anything not listed here (A4_AbilityChanges, A8_ImportedAbilities,
# and every abilities/*.cpp file) uses DEFAULT_ESDB (ESDB_A1.yml).
ESDB_FOR_SOURCE: dict[str, Path] = {
    "A9_DamageCalc": PARENT / "A_CoreBattle" / "EDSB_A9.yml",
    "B2_Backgrounds": PARENT / "B_Background" / "EDSB_B2.yml",
    "C1_LegendaryEncounters": PARENT / "C_LegendaryEncounter" / "ESDB_C1.yml",
    "D2_FieldOverlays": PARENT / "D_NonBattleItemChanges" / "ESDB_D2.yml",
}
DEFAULT_ESDB = PARENT / "A_CoreBattle" / "ESDB_A1.yml"

# Ability filenames whose stem doesn't camel-split into the exact enum
# suffix (acronyms, contractions, etc.) - add to this as new mismatches
# turn up rather than fighting the splitter.
NAME_OVERRIDES = {
    "RKSSystem": "RKS_SYSTEM",
    # CloudNine.cpp implements the shared Cloud Nine/Air Lock weather-nullify handler
    # (exports THUMB_BRANCH_EventAddAirLock) but checkDupes() in A8_ImportedAbilities.cpp
    # remaps ability 13 (Cloud Nine) -> 76 (Air Lock) before any dispatch lookup, so 76 is
    # the id that ever actually gets requested at runtime - building this as 13 would
    # produce a .dll that's never reachable.
    "CloudNine": "AIR_LOCK",
}


def parse_ability_ids(header_path: Path) -> dict[str, int]:
    text = header_path.read_text(encoding="utf-8", errors="replace")
    m = re.search(r"enum\s+AbilID\b.*?\{(.*?)\};", text, re.DOTALL)
    if not m:
        raise RuntimeError(f"Could not find 'enum AbilID {{...}}' in {header_path}")
    body = m.group(1)

    # ABIL165_TERAVOLT..ABIL181_TERAVOLT under #if ABILITY_EXPANSION are
    # placeholder duplicates (all = 0xA4), not real ids - drop that block.
    body = re.sub(r"#if\s+ABILITY_EXPANSION.*?#endif", "", body, flags=re.DOTALL)

    ids: dict[str, int] = {}
    for name, hexval in re.findall(r"ABIL\d+_([A-Z0-9_]+)\s*=\s*0x([0-9A-Fa-f]+)", body):
        ids[name] = int(hexval, 16)
    return ids


def stem_to_enum_name(stem: str) -> str:
    if stem in NAME_OVERRIDES:
        return NAME_OVERRIDES[stem]
    # "WellBakedBody" -> "WELL_BAKED_BODY", "IceBody" -> "ICE_BODY"
    return re.sub(r"(?<=[a-z0-9])(?=[A-Z])", "_", stem).upper()


def resolve_ability_sources() -> tuple[list[tuple[Path, str]], list[Path]]:
    """Returns (resolved [(source, output_stem)], unresolved [source])."""
    ability_ids = parse_ability_ids(ABILID_HEADER)
    resolved: list[tuple[Path, str]] = []
    unresolved: list[Path] = []
    for src in sorted(ABILITIES_DIR.glob("*.cpp")):
        enum_name = stem_to_enum_name(src.stem)
        ability_id = ability_ids.get(enum_name)
        if ability_id is None:
            unresolved.append(src)
        else:
            resolved.append((src, str(ability_id)))
    return resolved, unresolved


def resolve_top_level_sources() -> list[tuple[Path, str]]:
    return [
        (src, src.stem)
        for src in sorted(ROOT.glob("*.cpp"))
        if src.name not in TOP_LEVEL_EXCLUDE
    ]


def esdb_for(src: Path) -> Path:
    return ESDB_FOR_SOURCE.get(src.stem, DEFAULT_ESDB)


def rel(path: Path) -> str:
    """Path relative to PARENT (___BasicCodeInjectionForSharing), the root
    every printed/executed command runs from - matches commandprompts.txt."""
    return os.path.relpath(path, PARENT)


def dll_output_path(src: Path, output_stem: str) -> Path:
    if src.parent == ABILITIES_DIR:
        return DLL_LIB_DIR / f"{output_stem}.dll"
    return DLL_PATCH_DIR / f"{output_stem}.dll"


def compile_one(src: Path, output_stem: str, dry_run: bool) -> bool:
    out_path = OUTPUT_DIR / f"{output_stem}.elf"
    cmd = [str(GCC), *FLAGS, rel(src), "-o", rel(out_path)]
    print(" ".join(cmd))
    if dry_run:
        return True

    result = subprocess.run(cmd, cwd=PARENT, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  FAILED ({src.name}):")
        for line in (result.stderr or result.stdout).splitlines():
            print(f"    {line}")
        return False
    return True


def convert_to_dll(src: Path, output_stem: str, dry_run: bool) -> bool:
    esdb_path = esdb_for(src)
    if not dry_run and not esdb_path.exists():
        print(f"  DLL CONVERSION FAILED ({src.name}): ESDB not found at {esdb_path}")
        return False

    elf_path = OUTPUT_DIR / f"{output_stem}.elf"
    dll_path = dll_output_path(src, output_stem)
    if not dry_run:
        dll_path.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        "java", "-cp", rel(CTRMAP_JAR), "rpm.cli.RPMTool",
        "-i", rel(elf_path),
        "-o", rel(dll_path),
        "--esdb", rel(esdb_path),
        "--strip",
        # Without this, THUMB_BRANCH*-named functions just sit in the compiled
        # module with no hook actually installed anywhere - the module builds
        # fine but does nothing at runtime. This scans exported names for the
        # THUMB_BRANCH/THUMB_BRANCH_SAFESTACK/THUMB_BRANCH_LINK convention and
        # generates the relocation that patches the target (looked up in the
        # ESDB by the name after the prefix) to branch into this module.
        "--generate-relocations",
    ]
    is_ability = src.parent == ABILITIES_DIR
    if not is_ability:
        # Top-level branch-injected patches need the DLXF fourcc, matching the
        # already-deployed patches (confirmed via Tinke: A1/A2/A3/A5/A6/A8/B2
        # are all DLXF). Ability modules stay the RPMTool default (RPM0) since
        # they're genuinely dynamically loaded at runtime via k::dll::LoadLibrary.
        cmd += ["--fourcc", "DLXF"]
    print(" ".join(cmd))
    if dry_run:
        return True

    result = subprocess.run(cmd, cwd=PARENT, capture_output=True, text=True)
    output = result.stdout or ""
    hook_warnings = [line for line in output.splitlines() if "Could not create automated hook" in line]
    if hook_warnings:
        print(f"  HOOK WARNING ({src.name}): a THUMB_BRANCH* target didn't resolve in the ESDB - it compiled but won't hook at runtime:")
        for line in hook_warnings:
            print(f"    {line}")

    if result.returncode != 0:
        print(f"  DLL CONVERSION FAILED ({src.name}):")
        for line in (result.stderr or result.stdout).splitlines():
            print(f"    {line}")
        return False
    return not hook_warnings


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--dry-run", action="store_true", help="print commands and id resolution without compiling")
    parser.add_argument("--elf-only", action="store_true", help="compile only, skip the .elf -> .dll conversion step")
    parser.add_argument(
        "--group", choices=["all", "patches", "abilities"], default="all",
        help="which category to build: 'patches' = the 6 top-level branch-injected sources only, "
             "'abilities' = abilities/*.cpp only, 'all' = both (default)",
    )
    parser.add_argument(
        "only", nargs="*",
        help="only build sources matching one of these (case-insensitive substring match against the "
             "filename stem, e.g. 'field' matches D2_FieldOverlays.cpp, 'trace' matches abilities/Trace.cpp)",
    )
    args = parser.parse_args()

    if not GCC.exists() and not args.dry_run:
        print(f"error: compiler not found at {GCC}", file=sys.stderr)
        return 1
    if not args.elf_only and not CTRMAP_JAR.exists() and not args.dry_run:
        print(f"error: CTRMap.jar not found at {CTRMAP_JAR}", file=sys.stderr)
        return 1

    jobs: list[tuple[Path, str]] = []
    if args.group in ("all", "patches"):
        jobs += resolve_top_level_sources()
    if args.group in ("all", "abilities"):
        ability_resolved, ability_unresolved = resolve_ability_sources()
        jobs += ability_resolved
        if ability_unresolved:
            print("Could not resolve an ability id for:")
            for src in ability_unresolved:
                print(f"  {rel(src)}  (looked for enum entry '{stem_to_enum_name(src.stem)}')")
            print("These will be skipped. Add an entry to NAME_OVERRIDES in this script, or add the ability to A_Structs.h, and rerun.\n")

    if args.only:
        wanted = [token.lower() for token in args.only]
        jobs = [(src, out) for src, out in jobs if any(token in src.stem.lower() for token in wanted)]
        if not jobs:
            print(f"No sources matched: {', '.join(args.only)}", file=sys.stderr)
            return 1

    OUTPUT_DIR.mkdir(exist_ok=True)

    failures: list[Path] = []
    for src, out_stem in jobs:
        if not compile_one(src, out_stem, args.dry_run):
            failures.append(src)
            continue
        if not args.elf_only and not convert_to_dll(src, out_stem, args.dry_run):
            failures.append(src)

    print(f"\n{len(jobs) - len(failures)}/{len(jobs)} succeeded.")
    if failures:
        print("Failed:")
        for src in failures:
            print(f"  {rel(src)}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
