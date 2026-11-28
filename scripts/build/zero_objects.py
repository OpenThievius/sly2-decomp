# SPDX-License-Identifier: GPL-3.0-or-later
"""zero_objects.py: the objects a whole file defines in C that retail keeps as zeros inside `.rodata` (credited as matched data).

A whole file that defines a global with a constructor (`const RGBA RO_002A2900[256] = { RGBA(...), ... };`) gets a dynamically initialised object: g++
puts it in `.bss`, and the file's static initialiser fills it at run time. link_image.py links such an object by name at the address the name gives
(link_whole_data) and keeps retail's bytes there from the assembly piece. Retail holds zeros there, which is exactly the object's static image, so the
C object reproduces retail's bytes at its address and the range counts as matched data, as a data file's does. Only an object inside `.rodata` and
only over retail's all-zero bytes is credited (an object in retail's own `.bss` has no bytes in the file)."""


def zero_ranges(symbols, retail_bytes, low, high):
    """[(address, size)] of the symbols that are zero-initialised objects (section `.bss` or `.sbss`) at an address in [low, high) whose retail bytes
    are all zero. `symbols` is [(address, size, section name)], `retail_bytes(address, size)` the retail bytes there."""
    found = []
    for address, size, section in symbols:
        if section in ('.bss', '.sbss') and size and low <= address and address + size <= high and not any(retail_bytes(address, size)):
            found.append((address, size))
    return sorted(set(found))
