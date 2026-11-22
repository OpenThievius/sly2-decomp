// SPDX-License-Identifier: GPL-3.0-or-later
#include "light.h"
#include "sw.h"
extern "C" {
extern SW B_003DD490;
extern s32 B_003E19E4;

void func_001A3B38(LIGHT *plight) {
    if (plight->fDynamic == 0) {
        SW *psw = &B_003DD490;
        psw->frame = (s32) (psw->frame + 1);
    }
    if ((plight->fExcludeDynamicObjects == 0) && (plight->mode != 0)) {
        B_003E19E4 = 1;
    }
}

}
