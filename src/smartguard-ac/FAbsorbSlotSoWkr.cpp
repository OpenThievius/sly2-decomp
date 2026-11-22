// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "sly2.h"
struct EVENT { int kind; int gap[3]; VECTOR vec30; VECTOR vec20; int tail[4]; };
struct WKR { char pad[0x20]; VECTOR vec20; VECTOR vec30; char pad2[0x44 - 0x40]; unsigned grf; };
struct VT { char pad[0x198]; short delta; short index; void (*fn)(void *, EVENT *); };
struct OBJ { char pad[0xC]; VT *vptr; };
int FAbsorbSoWkr(SO *, WKR *);
extern "C" void SetSlotSoState(SLOTSO *, int);
int FAbsorbSlotSoWkr(SLOTSO *pso, WKR *pwkr)
{
    int fAbsorbed = FAbsorbSoWkr(pso, pwkr);
    if (fAbsorbed != 0 && (pwkr->grf & 8) != 0 && pso->state != 5) {
        SetSlotSoState(pso, 5);
        OBJ *pobj = (OBJ *)pso->field_0x1C8;
        if (pobj != 0) {
            EVENT event;
            event.kind = 6;
            event.vec20 = pwkr->vec20;
            event.vec30 = pwkr->vec30;
            VT *vtable = pobj->vptr;
            vtable->fn((char *)pobj + vtable->delta, &event);
        }
    }
    return fAbsorbed;
}
