// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A5630-0X2A5640 (piece rodata/new_17dd70). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: func_0017F5B0, func_0017F6B0.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

// data-ok: typed from func_0017F5B0 (a pointer to member function, virtual, vtable index 0x53, vtable pointer at 0xc), retail's bytes at 0X2A5630
extern const PMF D_002A5630 = {0, 0x53, {delta2: 0xc}};

// data-ok: typed from func_0017F6B0 (a pointer to member function, null), retail's bytes at 0X2A5638
extern const PMF D_002A5638 = {0, 0, {0}};
