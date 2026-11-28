// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A46C8-0X2A46D0 (piece rodata/aseg). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: PostAsegLoad.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void PostAsegLoadCallback();
}

// data-ok: typed from PostAsegLoad (a pointer to member function, non-virtual, PostAsegLoadCallback), retail's bytes at 0X2A46C8
extern const PMF D_002A46C8 = {0, -1, {PostAsegLoadCallback}};
