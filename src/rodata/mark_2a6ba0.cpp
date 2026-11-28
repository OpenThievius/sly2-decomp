// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file).
// Retail .rodata 0X2A6BA0-0X2A6BA8 (the last label of piece rodata/mark and the first byte of rodata/memcard_2a6ba7): a pointer to member
// function (MCPMF, include/memcard.h), the memcard thread's start callback. UpdateSave and SetSaveState copy it whole with an ldl/ldr pair
// (Splat labels its first and last byte, which split it over two pieces) and pass it to CreateMemcardThread, which stores it in MEMCARD::pmf.
#include "memcard.h"

struct SAVE;
extern "C" int CheckCardStatus(SAVE *psave);

// data-ok: typed from UpdateSave (a pointer to member function, non-virtual, CheckCardStatus), retail's bytes at 0X2A6BA0
extern const MCPMF g_2a6ba0 = {0, -1, (int (*)(void *))CheckCardStatus};
