// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A8278-0X2A8280 (piece rodata/so-po). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: func_001F4F10.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void func_001F7950();
}

// data-ok: typed from func_001F4F10 (a pointer to member function, non-virtual, func_001F7950), retail's bytes at 0X2A8278
extern const PMF D_002A8278 = {0, -1, {func_001F7950}};
