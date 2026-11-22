// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"

/* message 4's data: the gadget object it is about, in its second word */
struct GADGETMSG {
    u8 unknown_0x0[0x4];
    /* 0x4 */ GADGETOBJ *pgadget;
};

extern "C" {
void HandleLoMessage(LO *plo, int msgid, void *pv);

void HandleGadgetObjMessage(GADGETOBJ *pgadget, int msgid, void *pv) {
    HandleLoMessage(pgadget, msgid, pv);
    if (msgid == 4) {
        GADGETOBJ *pgadgetTarget = ((GADGETMSG *)pv)->pgadget;
        if (pgadgetTarget == pgadget && (u32)(pgadgetTarget->state - 1) < 2U) {
            pgadgetTarget->SetState(3);
        }
    }
}
}
