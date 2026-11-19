/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"

struct EA { float tLocal; int eatyp; int a; int b; };
struct ASEG { char pad0[0x50]; int dlAsega[3]; char pad5C[0xA8 - 0x5C]; int cea; EA *aea; };

struct ACT;
struct XF;
struct ALO;

struct BASICA {
    char pad0[0xC];
    virtual void AddRef();
    virtual void Release();
    virtual void HandleSpliceEvent(int event, int argument0, int argument1, int argument2, int argument3);
    virtual void PostMessage(int msgid, void *pv);
    virtual void HandleMessage(int msgid, void *pv);
    virtual void Slot6();
};

struct LOA : BASICA {
    virtual void Slot7(); virtual void Slot8(); virtual void Slot9(); virtual void Slot10();
    virtual void Slot11(); virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void Slot15(); virtual void Slot16(); virtual void Slot17(); virtual void Slot18();
    virtual void Slot19(); virtual void Slot20(); virtual void Slot21(); virtual void Slot22();
    virtual void Slot23(); virtual void Slot24(); virtual void Slot25(); virtual void Slot26();
    virtual void Slot27(); virtual void Slot28(); virtual void Slot29(); virtual void Slot30();
    virtual void Slot31(); virtual void Slot32(); virtual void Slot33(); virtual void Slot34();
    virtual void Slot35(); virtual void Slot36(); virtual void Slot37(); virtual void Slot38();
    virtual void Slot39(); virtual void Slot40(); virtual void Slot41(); virtual void Slot42();
    virtual void Slot43(); virtual void Slot44();
    virtual void Slot45(int arg);
};

struct ACTA { char pad0[4]; ALO *palo; XF *pxf; char padC[0x28 - 0xC]; ACTA *pactNext; };
struct HOOK { char pad0[8]; LOA *plo; int arg; HOOK *phookNext; };

struct ASEGA : BASICA {
    char pad10[4];
    ASEG *paseg;
    BASICA *ploOwner;
    float tLocal;
    char pad20[0x34 - 0x20];
    ACTA *pactFirst;
    HOOK *phookFirst;
    char pad3C[0x54 - 0x3C];
    int iea;
    char pad58[4];
    void *prefSfx;
};

extern "C" int FAsegaGone(ASEGA *);
extern "C" void HandleAsegaEvent(ASEGA *, EA *);
extern "C" void SetAsegaHandsOff(ASEGA *, int);
extern "C" void RemoveDlEntry(void *, void *);
extern "C" void RemoveXfAct(ALO *, XF *, ACTA *);
extern "C" void FreeAct(ACTA *);
extern "C" void func_0012CE70(HOOK *);
extern "C" void VirtualRefPtr_Assign(void *, void *);
extern "C" void PostLoMessage(ASEGA *, int, void *);
extern "C" int B_003E1218[];

struct REF {
    ASEGA *p;
    REF(ASEGA *q) { p = q; p->AddRef(); }
    ~REF() { p->Release(); }
};

extern "C" void RetractAsega(ASEGA *pasega)
{
    if (FAsegaGone(pasega))
        return;
    REF ref(pasega);
    while (pasega->iea < pasega->paseg->cea) {
        EA *pea = &pasega->paseg->aea[pasega->iea];
        pea->tLocal = pasega->tLocal;
        HandleAsegaEvent(pasega, pea);
        if (FAsegaGone(pasega))
            return;
        pasega->iea++;
    }
    SetAsegaHandsOff(pasega, 0);
    RemoveDlEntry(B_003E1218, pasega);
    RemoveDlEntry(pasega->paseg->dlAsega, pasega);
    ACTA *pact = pasega->pactFirst;
    while (pact) {
        ACTA *pactNext = pact->pactNext;
        RemoveXfAct(pact->palo, pact->pxf, pact);
        FreeAct(pact);
        pact = pactNext;
    }
    pasega->pactFirst = 0;
    HOOK *phook = pasega->phookFirst;
    while (phook) {
        HOOK *phookNext = phook->phookNext;
        phook->plo->Slot45(phook->arg);
        func_0012CE70(phook);
        phook = phookNext;
    }
    pasega->phookFirst = 0;
    VirtualRefPtr_Assign(&pasega->prefSfx, 0);
    pasega->HandleSpliceEvent(3, 0, 0, 0, 0);
    if (pasega->ploOwner)
        pasega->ploOwner->HandleMessage(2, pasega);
    PostLoMessage(pasega, 2, pasega);
    pasega->Release();
}
