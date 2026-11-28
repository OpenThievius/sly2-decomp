// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A5F98-0X2A5FA0 (piece rodata/jt-alo). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: func_0018E3A0.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void UpdateAllGuardLightStates();
}

// data-ok: typed from func_0018E3A0 (a pointer to member function, non-virtual, UpdateAllGuardLightStates), retail's bytes at 0X2A5F98
extern const PMF D_002A5F98 = {0, -1, {UpdateAllGuardLightStates}};
