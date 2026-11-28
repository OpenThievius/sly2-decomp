// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A4B58-0X2A4B70 (piece rodata/bomb-crusher_2a4b1c). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: AdjustLootNewXp.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void ReturnLootToGuard();
}

// data-ok: typed from AdjustLootNewXp (a pointer to member function, non-virtual, ReturnLootToGuard), retail's bytes at 0X2A4B58
extern const PMF D_002A4B58 = {0, -1, {ReturnLootToGuard}};

// data-ok: retail's bytes at 0X2A4B60
extern const unsigned int D_002A4B60[4] = {0, 0, 0xc51c4000, 0};
