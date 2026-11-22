// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"
#include "lo.h"
extern "C" {
void RetractAsega(BASIC *);
void RetractSma(BASIC *);
void CancelJumper(BASIC *);
void func_0020CA48(BASIC *);
}

/* the playing instance of an ANIMREF is a BASIC */
static inline BASIC *Pinst(ANIMREF *ref) { return (BASIC *)ref->pinst; }

void StopAnimref(ANIMREF *ref)
{
    switch (ref->kind) {
    case -1:
        return;
    case 0:
        if (!Pinst(ref)) return;
        RetractAsega(Pinst(ref));
        break;
    case 1:
        if (!Pinst(ref)) return;
        RetractSma(Pinst(ref));
        break;
    case 2:
        if (!Pinst(ref)) return;
        CancelJumper(Pinst(ref));
        break;
    case 3:
        if (!Pinst(ref)) return;
        func_0020CA48(Pinst(ref));
        break;
    default:
        return;
    }
    BASIC *pinst = Pinst(ref);
    pinst->Slot2();
    ref->pinst = 0;
}
