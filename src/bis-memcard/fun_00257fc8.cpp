// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
extern "C" {
void ResetSlotheap(SLOTHEAP *);
extern s32 B_002DD2D0;
extern s32 g_2dd2d4;
extern s32 B_002DD2D8;
extern s32 B_002DD2DC;
extern SLOTHEAP B_00452170;

void func_00257FC8(void) {
    B_002DD2D0 = 0;
    B_002DD2D8 = 0;
    B_002DD2DC = 0;
    g_2dd2d4 = 0;
    ResetSlotheap(&B_00452170);
}

}
