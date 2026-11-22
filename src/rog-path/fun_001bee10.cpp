// SPDX-License-Identifier: GPL-3.0-or-later
#include "rtalo.h"
extern "C" {
extern ROGWINDOW B_003E1A78[];
extern int *D_002C0BF8[];
s32 func_001BEE10(RTALO *prtalo, s32 index) {
    ROGWINDOW *pwindow = prtalo->pwindow;
    if (pwindow == 0) return -1;
    return D_002C0BF8[pwindow - B_003E1A78][index];
}
}
