/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
int WaitSema(int);
void func_00237AF8();
extern s32 D_002C4A84;
s32 func_00237B50(void) {
    func_00237AF8();
    WaitSema(D_002C4A84);
    return 0;
}
}
