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
// Fast-forward twin of HandleAsegaEvents (src/asega/HandleAsegaEvents.cpp). Retail reads iea and paseg
// through pasega in the forward test, then copies them ($a2, $a3) for the backward test: the source reads
// them once more into scoped locals (scoped so the goto to the shared switch does not cross their
// initialisation). HandleAsegaEvent takes (pasega, pea) only: its disassembly writes $a2/$a3 before reading.
extern "C" void HandleAsegaEventsFF(ASEGA *pasega)
{
    if (PtableOf(pasega)->cea == 0)
        return;
    REF ref(pasega);
    pasega->tTarget = pasega->tLocal;
    while (!FAsegaGone(pasega)) {
        float tTarget = pasega->tTarget;
        ASEGEVENT *pea;
        if (pasega->iea < PtableOf(pasega)->cea) {
            pea = (ASEGEVENT *)(pasega->iea * sizeof(ASEGEVENT) + (uptr)PtableOf(pasega)->aea);
            if (pea->tLocal <= tTarget && 0.0f <= pasega->svtLocal) {
                pasega->iea = pasega->iea + 1;
                goto dispatch;
            }
        }
        {
            ASEGEVENTTABLE *ptable = PtableOf(pasega);
            int iea = pasega->iea;
            if (iea > 0) {
                if (tTarget <= ((ASEGEVENT *)(iea * sizeof(ASEGEVENT) + (uptr)ptable->aea))[-1].tLocal && pasega->svtLocal < 0.0f) {
                    pasega->iea = iea - 1;
                    pea = (ASEGEVENT *)((uptr)ptable->aea + (iea - 1) * sizeof(ASEGEVENT));
                    goto dispatch;
                }
            }
        }
        pasega->tLocal = tTarget;
        break;
    dispatch:
        switch (pea->eatyp) {
        case 7: case 8: case 11: case 13: case 14: case 15: case 16:
        case 21: case 22: case 23: case 24:
            HandleAsegaEvent(pasega, pea);
            break;
        }
    }
}
