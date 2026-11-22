// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "gadgetobj.h"
extern "C" {
void HandleJtMessage(void *, int, int *);
void *PloLeaseCloneObject(void *, int);
void LockLeaseOfPlo(void *, void *);
void ThrowBentleyBomb(void *, int);
void HandleLookRigMessage(void *, int, int *);
void func_0018D698(void *, void *, int);
}
extern "C" void HandleBentleyMessage(BENTLEY *pbentley, int msgid, int *pv)
{
    HandleJtMessage(pbentley, msgid, pv);
    if (msgid != 1) {
        if (msgid == 9) {
            if (pv[0] == (int)pbentley->field_0x1030) {
                if (pv[2] == 0x216) {
                    void *plo = PloLeaseCloneObject(pbentley->pslotActive->ppool, 0);
                    pbentley->ploGadget = (LO *)plo;
                    LockLeaseOfPlo(pbentley->pslotActive->ppool, plo);
                    ((GADGETOBJ *)pbentley->ploGadget)->gadget = pbentley->pslotActive->gadget;
                    GADGETOBJ *pgadget = (GADGETOBJ *)pbentley->ploGadget;
                    pgadget->SetState(0);
                }
            } else if (pv[0] == pbentley->field_0x16CC) {
                if (pv[2] == 0x243)
                    ThrowBentleyBomb(pbentley, 0x80000);
            } else {
                HandleLookRigMessage(pbentley->PvLookRig(), 9, pv);
            }
        }
    } else {
        int islot;
        BENTLEYSLOT *pslot = pbentley->aslot;
        for (islot = 5; islot >= 0; islot--, pslot++) {
            if (pslot->plo == (LO *)pv)
                func_0018D698(pbentley, pslot, 0);
        }
    }
}
