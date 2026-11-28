# SPDX-License-Identifier: GPL-3.0-or-later
"""original_data.py: the data no compiler of ours can write (config/us/original_data.tsv), left out of the data totals of the report.

Permanent blockers are code that stays original assembly, so they are left out of the totals of progress/us/report.json (docs/build/vu0-mmi.md);
this is the same for data: the IOP modules (`.irx`), the VU microprograms (`.vutext`) and the machine code the SDK copies into kernel memory
are bytes of the executable that are not game data a C global can define. They are neither matched nor unmatched, so a share of data is a
share of the data C can define. The totals stay visible: make_objdiff.py writes progress/us/original_data.json (the bytes left out, by row)
and the README shows them beside the blockers (scripts/readme_progress.py). OpenThievius/sly1-decomp counts such data as matched instead
(its original_data.tsv, `.vutext` only); leaving it out is this project's choice, made by Theo on 2026-11-28 like the blockers.

A row is a whole data section (`.irx`, `.vutext`: the section is not a unit of the report at all) or a range inside a section (the kernel code:
the range is taken out of its section's unit)."""
import os


def read(path):
    """[{'name', 'address', 'size', 'kind', 'why'}] of config/us/original_data.tsv (address and size as integers)."""
    rows = []
    if not os.path.isfile(path):
        return rows
    with open(path, encoding='utf-8') as handle:
        for line in handle.read().split('\n')[1:]:
            columns = line.split('\t')
            if len(columns) >= 5 and columns[0]:
                rows.append({'name': columns[0], 'address': int(columns[1], 16), 'size': int(columns[2]), 'kind': columns[3], 'why': columns[4]})
    return rows


def covers_section(rows, address, size):
    """Whether one row is exactly this section (it is then no unit of the report)."""
    return any(row['address'] == address and row['size'] == size for row in rows)


def without_ranges(pieces, rows):
    """`pieces` ([(start, size, is_owned)], the pieces of one data section) with the parts that lie in a row's range taken out, a piece that
    crosses a boundary cut there. A range never overlaps a piece C owns: that is a mistake in the table and raises."""
    kept = []
    for start, size, is_owned in pieces:
        parts = [(start, start + size)]
        for row in rows:
            low, high = row['address'], row['address'] + row['size']
            cut = []
            for part_start, part_end in parts:
                if high <= part_start or low >= part_end:
                    cut.append((part_start, part_end))
                    continue
                if is_owned:
                    raise ValueError(f"original data {row['name']} {low:#x}-{high:#x} overlaps a range C owns ({start:#x}-{start + size:#x})")
                if low > part_start:
                    cut.append((part_start, low))
                if high < part_end:
                    cut.append((high, part_end))
            parts = cut
        kept.extend((part_start, part_end - part_start, is_owned) for part_start, part_end in parts)
    return kept


def summary(rows):
    """{'bytes': total, 'rows': [{'name', 'kind', 'bytes'}]}: what was left out, names and sizes only."""
    return {'bytes': sum(row['size'] for row in rows), 'rows': [{'name': row['name'], 'kind': row['kind'], 'bytes': row['size']} for row in rows]}
