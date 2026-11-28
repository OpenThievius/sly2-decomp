// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A8B08-0X2A8B10 (piece rodata/screen-font_2a8b08). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: LoadMovieCharacter.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void func_002155C0();
}

// data-ok: typed from LoadMovieCharacter (a pointer to member function, non-virtual, func_002155C0), retail's bytes at 0X2A8B08
extern const PMF D_002A8B08 = {0, -1, {func_002155C0}};
