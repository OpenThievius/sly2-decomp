// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "clock.h"
#include "gadgetobj.h"
#include "joy.h"
extern "C" {
int FAsegaGone(void *);
int FVjoyButtonHeld(JOY *, int);
int GrfbtnJtGadget(BENTLEY *, int);
void ReleaseBentleyGadget(BENTLEY *);
void SetBentleyGadgetAnim(BENTLEY *, int);
void SetJmpState(void *, int, int, int);
void StickGadgetObj(GADGETOBJ *, int);
}
void UpdateBentleyGadget(BENTLEY *pbentley)
{
    int state;
    for (;;) {
        state = pbentley->field_0x16B0;
        if (state == 0) {
            if (FAsegaGone(pbentley->field_0x1030))
                SetBentleyGadgetAnim(pbentley, 1);
        } else if (state >= 0) {
            if (state < 3) {
                GADGETOBJ *pgadget = (GADGETOBJ *)pbentley->ploGadget;
                int kind = pgadget->field_0x158;
                if (kind == 2) {
                    StickGadgetObj(pgadget, pgadget->field_0x1A0);
                    ReleaseBentleyGadget(pbentley);
                    SetJmpState(pbentley->PvJmp(), 0xB, 0, 0);
                } else if (kind == 4 || !FVjoyButtonHeld(pbentley->pjoy, GrfbtnJtGadget(pbentley, pbentley->pslotActive->gadget) | 0x10)) {
                    pgadget->vt->fn((char *)pgadget + pgadget->vt->delta, 1);
                    ReleaseBentleyGadget(pbentley);
                    SetJmpState(pbentley->PvJmp(), 0xB, 0, 0);
                } else {
                    if (g_2dded0.t - pbentley->tJump > 0.1f)
                        SetBentleyGadgetAnim(pbentley, 2);
                    else
                        SetBentleyGadgetAnim(pbentley, 1);
                }
            }
        }
        if (pbentley->field_0x16B0 == state || pbentley->state != 6)
            break;
    }
}
