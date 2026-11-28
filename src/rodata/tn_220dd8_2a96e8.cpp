// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A96E8-0X2A96F8 (piece rodata/tn_220dd8). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: RemoveTn, UpdateTn__FP2TNf.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void UpdateTnCallback();
}

// data-ok: typed from RemoveTn (a pointer to member function, null), retail's bytes at 0X2A96E8
extern const PMF D_002A96E8 = {0, 0, {0}};

// data-ok: typed from UpdateTn__FP2TNf (a pointer to member function, non-virtual, UpdateTnCallback), retail's bytes at 0X2A96F0
extern const PMF D_002A96F0 = {0, -1, {UpdateTnCallback}};
