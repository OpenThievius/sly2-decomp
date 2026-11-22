// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "sly2.h"
struct EVENT { int kind; u8 unknown_0x4[0xC]; VECTOR vec30; VECTOR vec20; u8 unknown_0x40[0x10]; };
struct WKR { u8 unknown_0x0[0x20]; VECTOR vec20; VECTOR vec30; u8 unknown_0x40[0x4]; unsigned grf; };
struct VT { u8 unknown_0x0[0x198]; short delta; short index; void (*fn)(void *, EVENT *); };
struct OBJ { u8 unknown_0x0[0xC]; VT *vptr; };
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
