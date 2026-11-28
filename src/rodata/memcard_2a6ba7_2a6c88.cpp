// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A6C88-0X2A6C98 (piece rodata/memcard_2a6ba7). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: func_001ABCE8, func_001ABD40.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void func_001ABBE0();
void func_001ABB60();
}

// data-ok: typed from func_001ABCE8 (a pointer to member function, non-virtual, func_001ABBE0), retail's bytes at 0X2A6C88
extern const PMF g_2a6c88 = {0, -1, {func_001ABBE0}};

// data-ok: typed from func_001ABD40 (a pointer to member function, non-virtual, func_001ABB60), retail's bytes at 0X2A6C90
extern const PMF D_002A6C90 = {0, -1, {func_001ABB60}};
