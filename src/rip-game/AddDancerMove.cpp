// SPDX-License-Identifier: GPL-3.0-or-later
#include "dancer.h"

void AddDancerMove(DANCER *dancer, s32 btn, s32 oid0, s32 grfAnim0, s32 oid1, s32 oid2) {
    s32 cmove = dancer->cmove;
    if ((u32) cmove < 8U) {
        dancer->cmove = cmove + 1;
        DANCERMOVE *move = &dancer->amove[cmove];
        move->btn = btn;
        move->astep[0].oid = oid0;
        move->astep[0].grfAnim = grfAnim0;
        move->astep[1].oid = oid1;
        move->astep[2].oid = oid2;
        move->astep[1].grfAnim = 0;
        move->astep[2].grfAnim = 0;
    }
}
