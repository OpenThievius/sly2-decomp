// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A85F8-0X2A8614 (piece rodata/step-rwm). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: PostGuardLoad.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void func_00206170();
}

// data-ok: retail's bytes at 0X2A85F8
extern const float D_002A85F8[2] = {-3.4028235e+38f, 0.0f};

// data-ok: retail's bytes at 0X2A8600
extern const float D_002A8600 = 3.4028235e+38f;

// data-ok: retail's bytes at 0X2A8604
extern const float D_002A8604 = -3.4028235e+38f;

// data-ok: typed from PostGuardLoad (a pointer to member function, non-virtual, func_00206170), retail's bytes at 0X2A8608
extern const PMF D_002A8608 = {0, -1, {func_00206170}};

// data-ok: retail's bytes at 0X2A8610
extern const float D_002A8610 = -3.4028235e+38f;
