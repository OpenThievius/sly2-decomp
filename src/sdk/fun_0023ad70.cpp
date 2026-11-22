/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
int RemoveDmacHandler(int, int);
int func_002351E0(int);
extern s32 B_0044EDD4;
extern s32 D_002C5A60;
void func_0023AD70(void) {
    func_002351E0(5);
    RemoveDmacHandler(5, B_0044EDD4);
    D_002C5A60 = 0;
}
}
