#include "asega.h"
/* The event table of an ASEG as these functions read it: a count at 0xA0 and the events at 0xA4 (asega.h names the two words iea and paea) */
struct ASEGEVENTTABLE { u8 unknown_0x0[0xA0]; s32 cea; ASEGEVENT *aea; };
static inline ASEGEVENTTABLE *PtableOf(ASEGA *pasega) { return (ASEGEVENTTABLE *)pasega->paseg; }
extern "C" int FAsegaGone(ASEGA *);
extern "C" void HandleAsegaEvent(ASEGA *, ASEGEVENT *);

struct REF {
    ASEGA *p;
    REF(ASEGA *q) { p = q; p->OnAdd(); }
    ~REF() { p->Slot2(); }
};
extern "C" void HandleAsegaEvents(ASEGA *pasega)
{
    if (PtableOf(pasega)->cea == 0)
        return;
    REF ref(pasega);
    float zero = 0.0f;
    pasega->tTarget = pasega->tLocal;
    while (!FAsegaGone(pasega)) {
        if (pasega->iea < PtableOf(pasega)->cea) {
            ASEGEVENT *pea = (ASEGEVENT *)(pasega->iea * sizeof(ASEGEVENT) + (uptr)PtableOf(pasega)->aea);
            float tEvent = pea->tLocal;
            if (tEvent < pasega->tTarget || (pasega->tTarget == tEvent && zero < pasega->svtLocal)) {
                pasega->iea = pasega->iea + 1;
                HandleAsegaEvent(pasega, pea);
                continue;
            }
        }
        ASEGEVENTTABLE *ptable = PtableOf(pasega);
        int iea = pasega->iea;
        if (iea > 0) {
            float tPrev = ((ASEGEVENT *)(iea * sizeof(ASEGEVENT) + (uptr)ptable->aea))[-1].tLocal;
            if (pasega->tTarget < tPrev || (pasega->tTarget == tPrev && pasega->svtLocal < zero)) {
                pasega->iea = iea - 1;
                HandleAsegaEvent(pasega, (ASEGEVENT *)((uptr)ptable->aea + (iea - 1) * sizeof(ASEGEVENT)));
                continue;
            }
        }
        pasega->tLocal = pasega->tTarget;
        break;
    }
}
