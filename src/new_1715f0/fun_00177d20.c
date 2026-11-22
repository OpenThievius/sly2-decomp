/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

/* two words of the guard only this function reads (one reader: a local view, not STEPGUARD members) */
struct GUARDVIEW_177D20 {
    u8 unknown_0x0[0xF94];
    /* 0xF94 */ s32 field_0xF94;
    u8 unknown_0xF98[0x10];
    /* 0xFA8 */ s32 field_0xFA8;
};

s32 func_00177D20(struct GOALBRAIN *goal) {
    struct GUARDVIEW_177D20 *pguard;
    s32 result;

    pguard = (struct GUARDVIEW_177D20 *)goal->pstep;
    result = 0;
    if ((pguard->field_0xFA8 != 0) || (pguard->field_0xF94 != 0)) {
        result = 1;
    }
    return result;
}
