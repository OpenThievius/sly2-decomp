// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A6768-0X2A6790 (piece rodata/new_1a1148). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: ZapTakeDamage.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void UpdateUbgSgs__FP3UBG();
void func_001A2028();
void func_001A1FA8();
void WarpZapToSafePoint();
}

// data-ok: typed from ZapTakeDamage (a pointer to member function, null), retail's bytes at 0X2A6768
extern const PMF D_002A6768 = {0, 0, {0}};

// data-ok: typed from ZapTakeDamage (a pointer to member function, non-virtual, UpdateUbgSgs__FP3UBG), retail's bytes at 0X2A6770
extern const PMF D_002A6770 = {0, -1, {UpdateUbgSgs__FP3UBG}};

// data-ok: typed from ZapTakeDamage (a pointer to member function, non-virtual, func_001A2028), retail's bytes at 0X2A6778
extern const PMF D_002A6778 = {0, -1, {func_001A2028}};

// data-ok: typed from ZapTakeDamage (a pointer to member function, non-virtual, func_001A1FA8), retail's bytes at 0X2A6780
extern const PMF D_002A6780 = {0, -1, {func_001A1FA8}};

// data-ok: typed from ZapTakeDamage (a pointer to member function, non-virtual, WarpZapToSafePoint), retail's bytes at 0X2A6788
extern const PMF D_002A6788 = {0, -1, {WarpZapToSafePoint}};
