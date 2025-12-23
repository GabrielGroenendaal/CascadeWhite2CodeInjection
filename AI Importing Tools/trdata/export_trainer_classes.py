import json
from pathlib import Path


def extract_class(data):
    if not isinstance(data, dict):
        return ""
    # Prefer human-readable class if available
    if "readable" in data and isinstance(data["readable"], dict) and "class" in data["readable"]:
        return str(data["readable"]["class"]) or ""
    # Fallbacks
    if "class" in data:
        return str(data["class"]) or ""
    if "raw" in data and isinstance(data["raw"], dict) and "class" in data["raw"]:
        return str(data["raw"]["class"]) or ""
    return ""


def main():
    base = Path(__file__).resolve().parent / "original"
    if not base.exists():
        print(f"Directory not found: {base}")
        return

    out_file = base / "trainer_classes.txt"
    classes = []

    def sort_key(p):
        s = p.stem
        try:
            return int(s)
        except Exception:
            return s

    for p in sorted(base.glob("*.json"), key=sort_key):
        try:
            text = p.read_text(encoding="utf-8")
            data = json.loads(text)
        except Exception as e:
            print(f"Skipping {p.name}: {e}")
            continue
        cls = extract_class(data)
        classes.append(cls)

    out_file.write_text("\n".join(classes), encoding="utf-8")
    print(f"Wrote {out_file} ({len(classes)} lines)")


if __name__ == "__main__":
    main()
