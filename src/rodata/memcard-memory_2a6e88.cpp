// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .rodata 0X2A6E88-0X2A6EF0 (piece rodata/memcard-memory). Its pointer-to-member constants are PMF (include/pmf.h): each reader copies one whole with
// an ldl/ldr pair (Splat labels its last byte, which split it in two) and passes it on: func_001AD168.
// The other globals are as make_data_files.py writes them.
#include "pmf.h"

extern "C" {
void FormatMemcard();
void func_001ABC68();
}

// data-ok: typed from func_001AD168 (a pointer to member function, non-virtual, FormatMemcard), retail's bytes at 0X2A6E88
extern const PMF D_002A6E88 = {0, -1, {FormatMemcard}};

// data-ok: typed from func_001AD168 (a pointer to member function, non-virtual, func_001ABC68), retail's bytes at 0X2A6E90
extern const PMF D_002A6E90 = {0, -1, {func_001ABC68}};

// data-ok: retail's bytes at 0X2A6E98
extern const char D_002A6E98[8] = "&2S&.: ";

// data-ok: retail's bytes at 0X2A6EA0
extern const char D_002A6EA0[16] = "&2S&. : ";

// data-ok: retail's bytes at 0X2A6EB0
extern const char D_002A6EB0[8] = "       ";

// data-ok: retail's bytes at 0X2A6EB8
extern const char D_002A6EB8[16] = " : &2T&.";

// data-ok: retail's bytes at 0X2A6EC8
extern const char D_002A6EC8[16] = "%s : %d%%";

// data-ok: retail's bytes at 0X2A6ED8
extern const char D_002A6ED8[8] = "\n";

// data-ok: retail's bytes at 0X2A6EE0
extern const char D_002A6EE0[16] = "episodeBest";
