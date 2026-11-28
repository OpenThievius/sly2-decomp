// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A6D88-0X2A6D90 (piece rodata/memcard-memory). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: MemcardMenu_Update, func_001AD168.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void CreateSaveFilesOnCard();
}

// data-ok: typed from MemcardMenu_Update, func_001AD168 (a pointer to member function, non-virtual, CreateSaveFilesOnCard), retail's bytes at 0X2A6D88
extern const PMF D_002A6D88 = {0, -1, {CreateSaveFilesOnCard}};
