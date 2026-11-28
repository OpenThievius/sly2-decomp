// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A5010-0X2A5020 (piece rodata/rip-game). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: PostRhythmLoad.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void BindRhythmCrowd();
}

// data-ok: typed from PostRhythmLoad (a pointer to member function, non-virtual, BindRhythmCrowd), retail's bytes at 0X2A5010
extern const PMF D_002A5010 = {0, -1, {BindRhythmCrowd}};

// data-ok: retail's bytes at 0X2A5018
extern const char D_002A5018[8] = "&2T&.";
