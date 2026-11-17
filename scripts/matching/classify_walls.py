#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""classify_walls.py [--write] [--min-runs N] [--min-arms N] [--stagnant N] - finds the unmatched functions that are walls by their history.

  .venv/bin/python scripts/matching/classify_walls.py --write      (from the repository root)

config/matching/walls.tsv lists the functions nobody should attempt without an unlocking finding (AGENTS.md). Rows of class `blocker`,
`fragment`, `helper`, `toolchain` and `tie` are written by hand with their reason. This tool adds the rest: a function that is still unmatched
(registry status `tried` or `todo`, not a permanent blocker), has at least --min-runs logged runs (default 20) from at least --min-arms
different arms (default 3), and has not improved in the last --stagnant runs (default 15) gets a row of class `exhausted`. The reason is its
history and the kind of difference `classify_diffs.py` found. Rows of class `exhausted` are the tool's own: each run rewrites them (a
function that matched, or that improved since, drops out); every other row is left alone. runs.log mixes toolchains, so this is a
measure of effort, not proof; the unlock column says what would justify a retry."""

import argparse
import collections
import csv
import os
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
WALLS = os.path.join(ROOT, "config", "matching", "walls.tsv")
FIELDS = ["address", "name", "class", "reason", "evidence", "unlock", "semantics", "fpu"]
UNLOCK = {
    "small": "a measured lever for this difference class (a flag row, a shared helper, an allocation rule) that takes another function of the class to 0 against a control; then rejudge",
    "structure": "a new reading of retail's block structure (a type, a field, an inline, a callee signature) that the earlier runs did not try, or a lever of the same kind as the small class; statement reordering is not one",
}


def load(path):
    with open(path, encoding="utf-8") as handle:
        return list(csv.DictReader(handle, delimiter="\t"))


def key(address):
    return int(address, 16)


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--min-runs", type=int, default=20)
    parser.add_argument("--min-arms", type=int, default=3)
    parser.add_argument("--stagnant", type=int, default=15)
    arguments = parser.parse_args()
    registry = {key(row["address"]): row for row in load(os.path.join(ROOT, "data/matching/functions.tsv"))}
    blockers = {key(row["address"]) for row in load(os.path.join(ROOT, "config/us/blockers.tsv"))}
    classes = {}
    classes_path = os.path.join(ROOT, "work/matching/classes.tsv")
    if os.path.exists(classes_path):
        classes = {key(row["address"]): row for row in load(classes_path)}
    runs = collections.defaultdict(list)
    with open(os.path.join(ROOT, "work/matching/runs.log"), encoding="utf-8") as handle:
        for line in handle:
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 4 and parts[3].lstrip("-").isdigit():
                runs[int(parts[2], 16)].append((parts[1].split("-")[0], int(parts[3])))
    existing = load(WALLS)
    manual = [row for row in existing if row["class"] != "exhausted"]
    walled = {key(row["address"]) for row in manual}
    found = []
    for address, history in runs.items():
        entry = registry.get(address)
        if not entry or entry["status"] not in ("tried", "todo") or address in walled or address in blockers:
            continue
        scores = [score for _, score in history]
        best = min(scores)
        if best == 0 or len(history) < arguments.min_runs or len({arm for arm, _ in history}) < arguments.min_arms:
            continue
        first_best = scores.index(best)
        since = len(scores) - 1 - first_best
        if since < arguments.stagnant:
            continue
        kind = classes.get(address, {}).get("class", "unclassified")
        reason = f"{len(history)} runs over {len({arm for arm, _ in history})} arms, best {best} first reached at run {first_best + 1}, none better in the last {since}; difference kind: {kind}"
        found.append(
            {
                "address": f"0x{address:X}",
                "name": entry["name"],
                "class": "exhausted",
                "reason": reason,
                "evidence": "work/matching/runs.log, classify_diffs.py",
                "unlock": UNLOCK["small" if best <= 16 else "structure"],
                "semantics": "",
                "fpu": "",
            }
        )
    found.sort(key=lambda row: key(row["address"]))
    count = collections.Counter("small" if int(row["reason"].split("best ")[1].split(" ")[0]) <= 16 else "structure" for row in found)
    print(f"{len(manual)} hand-written rows, {len(found)} exhausted ({dict(count)})")
    if arguments.write:
        with open(WALLS, "w", encoding="utf-8", newline="") as handle:
            writer = csv.DictWriter(handle, fieldnames=FIELDS, delimiter="\t", lineterminator="\n")
            writer.writeheader()
            writer.writerows(manual + found)
        print(f"wrote {WALLS}")


if __name__ == "__main__":
    sys.exit(main())
