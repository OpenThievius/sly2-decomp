// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"
#include "sly2.h"

extern "C" int FAsegaGone(ASEGA *);
extern "C" void HandleAsegaEvent(ASEGA *, ASEGEVENT *);
extern "C" void SetAsegaHandsOff(ASEGA *, int);
extern "C" void RemoveDlEntry(void *, void *);
extern "C" void RemoveXfAct(ALO *, XF *, ACT *);
extern "C" void FreeAct(ACT *);
extern "C" void func_0012CE70(PARTLINK *);
extern "C" void VirtualRefPtr_Assign(void *, void *);
extern "C" void PostLoMessage(ASEGA *, int, void *);
extern "C" DL B_003E1218;

/* RetractAsega's view of the segment: the retract events it replays from the handle's ieaRetract (asega.h leaves them undeclared:
   one reader, not a method of ASEG) */
struct ASEGRETRACT {
    u8 unknown_0x0[0xA8];
    /* 0xA8 */ s32 ceaRetract;
    /* 0xAC */ ASEGEVENT *aeaRetract;
};

struct REF {
    ASEGA *p;
    REF(ASEGA *q) { p = q; p->OnAdd(); }
    ~REF() { p->Slot2(); }
};

extern "C" void RetractAsega(ASEGA *pasega)
{
    if (FAsegaGone(pasega))
        return;
    REF ref(pasega);
    while (pasega->ieaRetract < ((ASEGRETRACT *)pasega->paseg)->ceaRetract) {
        ASEGEVENT *pea = &((ASEGRETRACT *)pasega->paseg)->aeaRetract[pasega->ieaRetract];
        pea->tLocal = pasega->tLocal;
        HandleAsegaEvent(pasega, pea);
        if (FAsegaGone(pasega))
            return;
        pasega->ieaRetract++;
    }
    SetAsegaHandsOff(pasega, 0);
    RemoveDlEntry(&B_003E1218, pasega);
    RemoveDlEntry(&pasega->paseg->dlAsega, pasega);
    ACTASEG *pact = pasega->pactFirst;
    while (pact) {
        ACTASEG *pactNext = pact->pactNext;
        RemoveXfAct(pact->act.palo, pact->act.pxf, &pact->act);
        FreeAct(&pact->act);
        pact = pactNext;
    }
    pasega->pactFirst = 0;
    PARTLINK *plink = pasega->plink;
    while (plink) {
        PARTLINK *plinkNext = plink->pnext;
        plink->plo->Slot45(plink->ipart);
        func_0012CE70(plink);
        plink = plinkNext;
    }
    pasega->plink = 0;
    VirtualRefPtr_Assign(&pasega->field_0x5C, 0);
    pasega->HandleSpliceEvent(3, 0, 0, 0, 0);
    if (pasega->paloRoot)
        pasega->paloRoot->HandleMessage(2, pasega);
    PostLoMessage(pasega, 2, pasega);
    pasega->Slot2();
}
