/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "slotso.h"

/* The message's data: an ACT, its word at 0x14 compared with the slot object's. */
struct ACT {
    u8 unknown_0x0[0x14];
    /* 0x14 */ s32 field_0x14; /* HandleSlotSoMessage */
};

extern "C" {
void HandleLoMessage(SLOTSO *, int, ACT *);
void SetSlotSoState(SLOTSO *, int);
}

extern "C" void HandleSlotSoMessage(SLOTSO *pslotso, int msgid, ACT *pact)
{
    HandleLoMessage(pslotso, msgid, pact);
    if (msgid == 2 && pact == pslotso->pactAnim) {
        if (pact->field_0x14 == pslotso->field_0x1A4) {
            SetSlotSoState(pslotso, 4);
        }
    }
}
