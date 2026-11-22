// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

// what the ANIMREF's pdata points at here: func_0020BB48 returns the word at 0x50
struct ANIMDATA {
    u8 unknown_0x0[0x50];
    s32 field_0x50;
};

s32 func_0020BB48(struct ANIMREF *panimref) {
    return ((struct ANIMDATA *)panimref->pdata)->field_0x50;
}
