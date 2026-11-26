// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "sly2.h"
#include "wkr.h"
#include "expl.h"
int FAbsorbSoWkr(SO *, WKR *);
extern "C" void SetSlotSoState(SLOTSO *, int);
int FAbsorbSlotSoWkr(SLOTSO *pso, WKR *pwkr)
{
    int fAbsorbed = FAbsorbSoWkr(pso, pwkr);
    if (fAbsorbed != 0 && (pwkr->flags & 8) != 0 && pso->state != 5) {
        SetSlotSoState(pso, 5);
        /* SLOTSO::field_0x1C8 is an explosion: it is called through EXPL's slot 51 with an EXPLSO */
        EXPL *pexpl = (EXPL *)pso->field_0x1C8;
        if (pexpl != 0) {
            EXPLSO explso;
            explso.grfexpl = 6;
            explso.pos = pwkr->pos;
            explso.vec = pwkr->vel;
            pexpl->ExplodeExplso(&explso);
        }
    }
    return fAbsorbed;
}
