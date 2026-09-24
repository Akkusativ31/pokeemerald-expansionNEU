#!/usr/bin/env python3
"""
Apply the PP overrides in pp_changes.txt to pokeemerald-expansion's moves_info.h.

Run from the repo root:
    python3 apply_pp.py            # dry run: shows what would change, writes nothing
    python3 apply_pp.py --apply    # writes the file (original saved once as moves_info.h.bak)

Options:
    --moves PATH     path to the moves file   (default: src/data/moves_info.h)
    --changes PATH   path to the PP list      (default: pp_changes.txt)

Safe to run repeatedly: it sets absolute values, so running it twice changes nothing more.
"""
import argparse
import re
import sys
from pathlib import Path

MOVE_HEADER = re.compile(r"^\s*\[(MOVE_[A-Z0-9_]+)\]\s*=")
PP_LINE = re.compile(r"(\.pp\s*=\s*)([^,\n]+)(,)")


def read(path):
    with open(path, newline="", encoding="utf-8") as f:
        return f.read()


def write(path, text):
    with open(path, "w", newline="", encoding="utf-8") as f:
        f.write(text)


def load_changes(path):
    changes = {}
    for lineno, raw in enumerate(read(path).splitlines(), 1):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) != 2 or not parts[0].startswith("MOVE_") or not parts[1].isdigit():
            sys.exit(f"{path}:{lineno}: cannot parse '{raw.strip()}' (expected: MOVE_NAME NUMBER)")
        pp = int(parts[1])
        if not 1 <= pp <= 64:
            sys.exit(f"{path}:{lineno}: PP {pp} is out of range (1-64)")
        if parts[0] in changes:
            print(f"warning: {parts[0]} appears more than once, using the last value ({pp})")
        changes[parts[0]] = pp
    return changes


def apply(text, changes):
    out = []
    current = None
    done = {}      # move -> (old, new)
    seen = set()   # every move found in the file
    for line in text.splitlines(keepends=True):
        m = MOVE_HEADER.match(line)
        if m:
            current = m.group(1)
            seen.add(current)
        elif current in changes:
            p = PP_LINE.search(line)
            if p:
                old = p.group(2).strip()
                new = str(changes[current])
                line = line[:p.start(2)] + new + line[p.end(2):]
                done[current] = (old, new)
                current = None  # only the first .pp per move
        out.append(line)
    return "".join(out), done, seen


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--apply", action="store_true", help="write the changes (default is a dry run)")
    ap.add_argument("--moves", default="src/data/moves_info.h")
    ap.add_argument("--changes", default="pp_changes.txt")
    args = ap.parse_args()

    moves_path, changes_path = Path(args.moves), Path(args.changes)
    for p in (moves_path, changes_path):
        if not p.exists():
            sys.exit(f"File not found: {p}  (run this from the repo root, or use --moves / --changes)")

    changes = load_changes(changes_path)
    new_text, done, seen = apply(read(moves_path), changes)

    changed = {m: v for m, v in done.items() if v[0] != v[1]}
    unchanged = [m for m, v in done.items() if v[0] == v[1]]
    missing = sorted(m for m in changes if m not in seen)
    no_pp = sorted(m for m in changes if m in seen and m not in done)

    print(f"{len(changes)} moves in list | {len(changed)} will change | {len(unchanged)} already correct\n")
    for move in sorted(changed):
        old, new = changed[move]
        print(f"  {move:<28} {old} -> {new}")

    if missing:
        print("\nNOT FOUND in the moves file (name wrong, or move doesn't exist in your version):")
        for m in missing:
            print(f"  {m}")
    if no_pp:
        print("\nFound, but no '.pp = ...,' line was located:")
        for m in no_pp:
            print(f"  {m}")

    if not args.apply:
        print("\nDry run only. Run again with --apply to write the changes.")
        return

    bak = moves_path.with_name(moves_path.name + ".bak")
    if not bak.exists():
        write(bak, read(moves_path))
        print(f"\nBackup saved: {bak}")
    write(moves_path, new_text)
    print(f"Written: {moves_path}")


if __name__ == "__main__":
    main()
