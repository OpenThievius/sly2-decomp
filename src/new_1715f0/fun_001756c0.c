/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

/* message 0xB: the object (a guard's target) the message reports */
struct MSGHIT {
    u8 unknown_0x0[0x4];
    /* 0x4 */ struct LO *pobj;
};

s32 Goal_FHandleMessage(struct GOALREACT *goal, s32 msgid, void *pv);
void *func_00174898(struct LO *plo);

s32 func_001756C0(struct GOALREACT *goal, s32 msgid, struct MSGHIT *pmsg) {
    struct LO *pobj;

    if (msgid == 0xB) {
        pobj = pmsg->pobj;
        if (pobj == goal->ptarget) {
            if (func_00174898(pobj) == goal->pstep) {
                goal->fHit = 1;
                return 1;
            }
        }
    }
    return Goal_FHandleMessage(goal, msgid, pmsg);
}
