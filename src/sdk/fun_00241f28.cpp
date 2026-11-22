/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
int func_00235518(int);
int func_00236960(const char *, ...);
int sceSifCheckStatRpc(void *);
extern s32 D_002C6750;
extern s32 D_002C82C0[];
s32 func_00241F28(s32 block) {
    if (block == 0) {
        if (D_002C6750 > 0) {
            func_00236960("S cmd wait\n");
        }
        while (sceSifCheckStatRpc(D_002C82C0) != 0) {
            func_00235518(0xFA0);
        }
        return 0;
    }
    return sceSifCheckStatRpc(D_002C82C0);
}
}
