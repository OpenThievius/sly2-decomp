// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A4D10-0X2A4D20 (piece rodata/new_13f888). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: PostJtLoad.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void func_00143BD8();
}

// data-ok: typed from PostJtLoad (a pointer to member function, non-virtual, func_00143BD8), retail's bytes at 0X2A4D10
extern const PMF D_002A4D10 = {0, -1, {func_00143BD8}};

// data-ok: retail's bytes at 0X2A4D18
extern const float D_002A4D18[2] = {3.4028235e+38f, 0.0f};
