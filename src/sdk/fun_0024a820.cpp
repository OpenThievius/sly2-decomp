/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
char *func_0024A7B0(void);
extern char D_002C8378[0xE];
s32 func_0024A820(void) {
    if (D_002C8378[0] == 0) {
        func_0024A7B0();
    }
    return D_002C8378[4] == 0x54;
}
}
