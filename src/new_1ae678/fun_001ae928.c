/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pausemenu.h"

struct LO;
struct SW;
struct LO *PloFindSwObject_thunk(struct SW *psw, s32 grffso, s32 oid, struct LO *ploContext);
extern struct SW B_003DD490;

void func_001AE928(PAUSEMENU *pmenu) {
    pmenu->pblot = (PAUSEBLOT *)PloFindSwObject_thunk(&B_003DD490, 0x405, 0x370, 0);
    pmenu->depthNext = -1;
    pmenu->state = 0;
}
