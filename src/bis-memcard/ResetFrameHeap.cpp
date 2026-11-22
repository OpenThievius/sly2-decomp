// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
extern "C" {
void ResetSlotheap(SLOTHEAP *);
extern s32 B_002DD2A0;
extern s32 B_002DD2A4;
extern s32 B_002DD2A8;
extern s32 B_002DD2AC;
extern SLOTHEAP B_004520F8;

void ResetFrameHeap(void) {
    B_002DD2A0 = 0;
    B_002DD2A8 = 0;
    B_002DD2AC = 0;
    B_002DD2A4 = 0;
    ResetSlotheap(&B_004520F8);
}

}
