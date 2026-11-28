// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A8270-0X2A8278 (piece rodata/sm-so). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: AddSoLoHierarchy, RemoveSoLoHierarchy.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void func_001F3868();
}

// data-ok: typed from AddSoLoHierarchy, RemoveSoLoHierarchy (a pointer to member function, non-virtual, func_001F3868), retail's bytes at 0X2A8270
extern const PMF D_002A8270 = {0, -1, {func_001F3868}};
