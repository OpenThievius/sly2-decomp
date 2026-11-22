/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

/* a guard of class 0x3C (60, a STEPGUARD subclass): the word past STEPGUARD it holds (GoalBrain_SetCommand, command 15, reads it too) */
struct GUARD3CVIEW {
    u8 unknown_0x0[0x108C];
    /* 0x108C */ struct LO *field_0x108C;
};

s32 FIsBasicDerivedFrom(void *pbasic, s32 classIndex);

s32 func_00177D70(struct GOALBRAIN *goal) {
    s32 result;

    result = 0;
    if (FIsBasicDerivedFrom(goal->pstep, 0x3C) != 0) {
        result = ((struct GUARD3CVIEW *)goal->pstep)->field_0x108C != 0;
    }
    return result;
}
