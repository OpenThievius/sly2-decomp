// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A5140-0X2A5160 (piece rodata/emitter_1591b0). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: CEmitter_PostLoad.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void AttachEmitterToReference();
}

// data-ok: typed from CEmitter_PostLoad (a pointer to member function, non-virtual, AttachEmitterToReference), retail's bytes at 0X2A5140
extern const PMF D_002A5140 = {0, -1, {AttachEmitterToReference}};

// data-ok: retail's bytes at 0X2A5148
extern const float D_002A5148 = 3.4028235e+38f;

// data-ok: retail's bytes at 0X2A514C
extern const float D_002A514C = 3.4028235e+38f;

// data-ok: retail's bytes at 0X2A5150
extern const float D_002A5150[4] = {3.4028235e+38f, 0.0f, 0.0f, 0.0f};
