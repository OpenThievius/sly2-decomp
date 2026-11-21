#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""check_cleanup.py --base <ref>: the rules of docs/contributing/code-cleanup.md on what a change adds (the lines it adds to src/ and
include/, and the files it adds anywhere), so older problems on main do not fail a new pull request. Exit 1 when a rule is broken."""
import argparse
import re
import subprocess
import sys

CODE = re.compile(r'^(src|include)/.+\.(c|cpp|h)$')
FORBIDDEN_FILES = re.compile(r'(^|/)(SCUS_\d+\.\d+|.*\.(elf|iso|bin|irx|o|s|ee|vu|gpr))$|^(work|build)/|^tools/(?!README\.md$)')
LINE_RULES = (
    (re.compile(r'M2C_(UNK|FIELD)\b'), 'M2C_UNK / M2C_FIELD: write the struct field (include/sly2.h) instead of the raw offset'),
    (re.compile(r'/\* Error'), 'a `/* Error` comment from m2c: resolve it'),
    (re.compile(r'\b(unk_[0-9A-Fa-f]+|phi_[a-z0-9_]+|saved_reg_\w+)\b'), 'an m2c temporary name (unk_, phi_, saved_reg_): name it'),
    (re.compile(r'[ \t]+$'), 'trailing whitespace'),
    (re.compile(r'\t'), 'a tab: use four spaces'),
)

SOURCE_RULES = (  # src/ only: include/types.h is where these live
    (re.compile(r'\btypedef\s+[^;{}]+?\s+(s8|u8|s16|u16|s32|u32|s64|u64|s128|u128|f32|f64|QW)\s*(__attribute__\s*\(\(.*?\)\))?\s*;'),
     'a local fixed-width typedef: include "types.h" (or sly2.h) instead'),
)

SOURCE_WARNING_RULES = (  # src/ only: the shared header defines it
    (re.compile(r'\bstruct\s+(SO|LO|BASIC|SLOTSO|DL|DLE|DLI|XF|CRef|SW|SLOTHEAP|ALLOCREQ|PO|STEP|JT|SLY|MURRAY|BENTLEY|STEPGUARD|GUARD|GOAL|MPEGDEC|MPEGBUFFER|MPEGBLOCK|MPEGHANDLE)\s*\{'), 'a local copy of a shared type: include its header from include/ (add the field there, see the rule in lo.h)'),
)

WARNING_RULES = (  # the tie-break rule (docs/PRESERVATION_AND_PORT.md): printed, never fail the check
    (re.compile(r'\b(char|u8|s8)\s+pad\w*\s*\['), 'a padding member: prefer the shared type from include/ (add the field there)'),
    (re.compile(r'\*\s*\(\s*[\w ]+\*+\s*\)\s*\(.*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)'), 'a cast offset: prefer the struct member'),
    (re.compile(r'->\s*delta\b'), 'a hand-written vtable call: prefer a virtual member function when it matches'),
    (re.compile(r'^(?!\s*typedef\b).*\blong\b'), 'a bare long: prefer s64 (64 bits) or QW (128 bits)'),
)

def parse_diff(text):
    """{path: [(line number, added line)]} of a `git diff -U0`."""
    added, path, number = {}, None, 0
    for line in text.split('\n'):
        if line.startswith('+++ '):
            path = line[6:] if line.startswith('+++ b/') else None
        elif line.startswith('@@'):
            number = int(re.search(r'\+(\d+)', line).group(1)) - 1
        elif path and line.startswith('+'):
            number += 1
            added.setdefault(path, []).append((number, line[1:]))
    return added

def check_lines(added):
    """Problems (path:line: rule) in the added lines of code files."""
    return [f'{path}:{number}: {message}' for path, lines in sorted(added.items()) if CODE.match(path)
            for number, text in lines for pattern, message in LINE_RULES + (SOURCE_RULES if path.startswith('src/') else ())
            if pattern.search(text)]

def warn_lines(added):
    """Tie-break warnings (path:line: warning: rule) in the added lines of code files; they do not fail the check."""
    return [f'{path}:{number}: warning: {message}' for path, lines in sorted(added.items()) if CODE.match(path)
            for number, text in lines for pattern, message in WARNING_RULES + (SOURCE_WARNING_RULES if path.startswith('src/') else ())
            if pattern.search(text)]

def check_files(paths):
    """Problems for added files that could be game data or build output."""
    return [f'{path}: game data or build output must not be committed (see .gitignore)' for path in paths if FORBIDDEN_FILES.search(path)]

TREE_METRICS = (  # --all: what is left to clean in matched code, counted per module (ROADMAP item 1)
    ('local_shared_type', SOURCE_WARNING_RULES[0][0]),
    ('padding', WARNING_RULES[0][0]),
    ('cast_offset', WARNING_RULES[1][0]),
    ('char_offset', re.compile(r'\(\s*(char|u8)\s*\*\s*\)\s*\w+\s*\+\s*(0x[0-9A-Fa-f]+|\d+)')),
    ('vtable_call', WARNING_RULES[2][0]),
    ('m2c_macro', LINE_RULES[0][0]),
    ('bare_long', WARNING_RULES[3][0]),
)

def module_of(path):
    """The module of a source in src/: its folder under src/ (a file directly in src/ is its own module)."""
    parts = path.split('/')
    return parts[1] if len(parts) > 2 else parts[-1]

def tree_counts(sources):
    """{module: {metric: lines}} over (path, text) pairs of sources in src/; every module gets every metric, zero included."""
    counts = {}
    for path, text in sources:
        if not (CODE.match(path) and path.startswith('src/')):
            continue
        row = counts.setdefault(module_of(path), dict.fromkeys((name for name, _ in TREE_METRICS), 0))
        for name, pattern in TREE_METRICS:
            row[name] += sum(1 for line in text.split('\n') if pattern.search(line))
    return counts

def print_tree_counts(counts):
    """A TSV: one row per module, most to clean first, then a total row."""
    names = [name for name, _ in TREE_METRICS]
    print('\t'.join(['module'] + names))
    totals = dict.fromkeys(names, 0)
    for module, row in sorted(counts.items(), key=lambda item: (-sum(item[1].values()), item[0])):
        print('\t'.join([module] + [str(row[name]) for name in names]))
        for name in names:
            totals[name] += row[name]
    print('\t'.join(['total'] + [str(totals[name]) for name in names]))

def main():
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--base', help='check what HEAD adds over this ref')
    group.add_argument('--all', action='store_true', help='count the tie-break patterns over every tracked source in src/, per module')
    arguments = parser.parse_args()
    if arguments.all:
        paths = subprocess.check_output(['git', 'ls-files', 'src'], text=True).split()
        sources = []
        for path in paths:
            with open(path, encoding='utf-8', errors='replace') as handle:
                sources.append((path, handle.read()))
        print_tree_counts(tree_counts(sources))
        return
    diff = subprocess.check_output(['git', 'diff', '-U0', '--diff-filter=AM', arguments.base, 'HEAD'], text=True)
    new_files = subprocess.check_output(['git', 'diff', '--name-only', '--diff-filter=A', arguments.base, 'HEAD'], text=True).split()
    added = parse_diff(diff)
    problems = check_lines(added) + check_files(new_files)
    warnings = warn_lines(added)
    if warnings:
        print('\n'.join(warnings))
        print(f'{len(warnings)} tie-break warnings (docs/contributing/code-cleanup.md): not failures')
    print('\n'.join(problems) if problems else 'cleanup rules: ok')
    sys.exit(1 if problems else 0)

if __name__ == '__main__':
    main()
