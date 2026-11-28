// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A4BB0-0X2A4BB8 (piece rodata/new_13cf38). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: Crfodb_OnAdd.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void Crfodb_SpawnLoot();
}

// data-ok: typed from Crfodb_OnAdd (a pointer to member function, non-virtual, Crfodb_SpawnLoot), retail's bytes at 0X2A4BB0
extern const PMF D_002A4BB0 = {0, -1, {Crfodb_SpawnLoot}};
