// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
extern "C" {
void ResetSlotheap(SLOTHEAP *);
extern s32 B_002DD2B0;
extern s32 B_002DD2B4;
extern s32 B_002DD2B8;
extern s32 B_002DD2BC;
extern SLOTHEAP B_00452120;

void ResetProcHeap(void) {
    B_002DD2B0 = 0;
    B_002DD2B8 = 0;
    B_002DD2BC = 0;
    B_002DD2B4 = 0;
    ResetSlotheap(&B_00452120);
}

}
