// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A4B10-0X2A4B1C (piece rodata/bomb). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: func_0013AEB0.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

// data-ok: typed from func_0013AEB0 (a pointer to member function, virtual, vtable index 0x4e, vtable pointer at 0xc), retail's bytes at 0X2A4B10
extern const PMF D_002A4B10 = {0, 0x4e, {delta2: 0xc}};

// data-ok: retail's bytes at 0X2A4B18
extern const float D_002A4B18 = 3.4028235e+38f;
