# SPDX-License-Identifier: GPL-3.0-or-later
"""delay_slots.py: the delay-slot placement of the assembler that built Sony's libraries, for the SDK range (config/us/sony_gcc29.txt).

Sony's ee-gcc 2.9-ee-991111 never puts a volatile access into a delay slot: it marks the access with `#.set volatile` / `#.set novolatile`
(comments in its output) and leaves the `jal` after a volatile store in reorder mode with an empty slot. The assembler we have for that
range then adds a `nop`; retail's moved the store into the slot (0x24B480 sceMpegInit: `jal InitIpu` with `sw $zero, 0($v1)` in its slot).
This rewrites the compiler's assembly text the way that assembler did: a volatile store that directly precedes a reorder-mode `jal` or
return moves into its slot, under `.set noreorder`. A store to a symbol or a constant address keeps the assembler's `lui $at` before the
jump and the `sw ...($at)` goes into the slot.

Applied to the compiler's output of every `sony29` function by scripts/build/compile_unit.py; nothing else uses the text. The rule and its
measurements are in docs/build/assembler.md ("Delay slots of the SDK range"). Written for this repository from the retail words of the
functions it moves; the same idea is in OpenThievius/sly1-decomp's tools/volatile_slots.py and OpenRAC's rac1-decomp (THIRD_PARTY_NOTICES.md).

    python3 scripts/build/delay_slots.py IN.s [OUT.s]    (rewrites IN.s in place without OUT.s)
"""
import re
import sys

STORE = re.compile(r'^\s*(sb|sh|sw|sd)\s+(\$\w+),\s*(\S.*?)\s*$')
BASED = re.compile(r'^(.*)\((\$\w+)\)$')
JUMP_AND_LINK = re.compile(r'^\s*jal\s+\S+\s*$')
RETURN = re.compile(r'^\s*j\s+\$(31|ra)\s*$')
RETURN_ADDRESS = ('$31', '$ra')


def is_instruction(line):
    stripped = line.strip()
    return bool(stripped) and not stripped.startswith(('#', '.')) and not stripped.endswith(':')


def store_with_assembler_pair(operation, register, address, jump):
    """The three lines of a store to a symbol or a constant address around `jump`: the assembler's `lui $at`, the jump, the store through $at.
    A constant's high half carries the sign of its low half (`sw $3, 0x1000b000` is `lui $at, 0x1001` and `sw $3, -20480($at)`)."""
    try:
        value = int(address, 0)
    except ValueError:
        value = None
    if value is None:
        high, low = f'%hi({address})', f'%lo({address})'
    else:
        low = ((value & 0xFFFF) ^ 0x8000) - 0x8000
        high, low = str(((value - low) >> 16) & 0xFFFF), str(low)
    return [f'\tlui\t$1,{high}', jump, f'\t{operation}\t{register},{low}($1)']


def fits_a_slot(operation_line):
    """Whether the volatile store may be moved: it does not use the return address, which the jump overwrites."""
    match = STORE.match(operation_line)
    based = BASED.match(match.group(3))
    return match.group(2) not in RETURN_ADDRESS and not (based and based.group(2) in RETURN_ADDRESS)


def fill(assembly):
    """The assembly with each volatile store that directly precedes a reorder-mode `jal` or return moved into the slot of that jump."""
    out = []
    reorder = True
    volatile = False
    store = None  # index in `out` of the last volatile store, while only comments follow it
    for line in assembly.split('\n'):
        stripped = line.strip()
        if stripped.replace(' ', '\t') == '.set\tnoreorder':
            reorder = False
        elif stripped.replace(' ', '\t') == '.set\treorder':
            reorder = True
        if stripped.replace(' ', '\t') == '#.set\tvolatile':
            volatile = True
        elif stripped.replace(' ', '\t') == '#.set\tnovolatile':
            volatile = False
        if reorder and store is not None and (JUMP_AND_LINK.match(line) or RETURN.match(line)) and fits_a_slot(out[store]):
            operation, register, address = STORE.match(out[store]).groups()
            based = BASED.match(address)
            del out[store]
            out.append('\t.set\tnoreorder')
            out.extend([line, f'\t{operation}\t{register},{address}'] if based else store_with_assembler_pair(operation, register, address, line))
            out.append('\t.set\treorder')
            store = None
            continue
        if is_instruction(line):
            store = len(out) if (volatile and reorder and STORE.match(line)) else None
        elif stripped and not stripped.startswith('#'):
            store = None  # a label or a directive: nothing moves across it
        out.append(line)
    return '\n'.join(out)


def main(arguments=None):
    arguments = sys.argv[1:] if arguments is None else arguments
    source = arguments[0]
    destination = arguments[1] if len(arguments) > 1 else source
    with open(source, encoding='utf-8') as handle:
        text = handle.read()
    with open(destination, 'w', encoding='utf-8') as handle:
        handle.write(fill(text))


if __name__ == '__main__':
    main()
