// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A6BA8-0X2A6C50 (piece rodata/memcard_2a6ba7). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: SetSaveState.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void ScanSaveDirectory();
}

// data-ok: typed from SetSaveState (a pointer to member function, non-virtual, ScanSaveDirectory), retail's bytes at 0X2A6BA8
extern const PMF g_2a6ba8 = {0, -1, {ScanSaveDirectory}};

// data-ok: retail's bytes at 0X2A6BB0
extern const char D_002A6BB0[24] = "/BASCUS-97316YAOTWTD!";

// data-ok: retail's bytes at 0X2A6BC8
extern const char D_002A6BC8[48] = "/BASCUS-97316YAOTWTD!/BASCUS-97316YAOTWTD!";

// data-ok: retail's bytes at 0X2A6BF8
extern const char D_002A6BF8[8] = "Sly 2";

// data-ok: retail's bytes at 0X2A6C00
extern const char D_002A6C00[8] = "/";

// data-ok: retail's bytes at 0X2A6C08
extern const char D_002A6C08[32] = "/BASCUS-97316YAOTWTD!/icon.sys";

// data-ok: retail's bytes at 0X2A6C28
extern const char D_002A6C28[40] = "/BASCUS-97316YAOTWTD!/memcard_icon.ico";
