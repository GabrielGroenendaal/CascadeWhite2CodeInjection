# trdata converter

Small utility to convert labeled trainer-blocks into `trdata` JSON files compatible with the project's `trdata/original/*.json` format.

Usage:

```bash
python trdata/convert_trdata.py --input ___InputData/Trainers_InputSample.txt --output trdata/edited
```

Options:
- `--maps` : path to mapping files (default `___MAPS`). Expects `Trainers.txt` to map trainer name → id if available.
- `--original` : path to `trdata/original` (default `trdata/original`) used to copy defaults like `money` and `reward_item`.

Input format (per-block):
- Line 1: Trainer Name (optional modifier in parentheses, e.g. `Rival (2x)`).
- Line 2: Pokemon names (comma-separated, or `|`-separated, or quoted words).
- Subsequent lines: labeled fields like `Item:`, `Level:`, `Nature:`, `Ability:`, `Move 1:`, `Move 2:`, `Move 3:`, `Move 4:` with lists that match the number of Pokemon.

The script validates counts and writes one JSON file per trainer to the output directory named `<trainerId>.json`.
