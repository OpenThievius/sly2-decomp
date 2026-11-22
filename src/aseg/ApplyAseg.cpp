// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
#include "alo.h"
#include "asega.h"
#include "sw.h"
#include "sly2.h"

void *PvAllocSlotheapImpl(SLOTHEAP *);

static inline float GFromClq(CLQ *pclq, float g) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static inline float GLimitLm(LM *plm, float g)
{
    float gMin = plm->gMin;
    float gMax = plm->gMax;
    if (g < gMin)
        g = gMin;
    else if (gMax < g)
        g = gMax;
    return g;
}
/* Holds a reference on a handle for the rest of ApplyAseg (slot 1 retains, slot 2 releases) */
struct ASEGALOCK {
    ASEGA *p;
    ASEGALOCK(ASEGA *pasega) { p = pasega; p->OnAdd(); }
    ~ASEGALOCK() { p->Slot2(); }
};
/* retail sets the handle's vtable pointer (0xC) by hand: the handle comes from a slot heap, not from new */
struct ASEGAVTABLE {
    u8 unknown_0x0[0xC];
    void *vtable;
};
extern "C" {
extern SLOTHEAP B_003E1224;
extern DL B_003E1218; /* every playing handle (ibDle 0x2C like ASEG::dlAsega) */
extern char B_002DE578[];
extern void *D_002CAF48[]; /* the handle's vtable */
extern void *D_002CAF08[]; /* the act kind 0's vtable */
float GetSuck(void *);
void SetAsegaSpeed(ASEGA *, float);
void AppendDlEntry(DL *, void *);
void CFramePtr_Assign(void *, void *);
void BindAsegChn(ASEG *, ALO *, ASEGCHN *, SO **, XF **);
void func_001F8668(SO *, int);
void *PvAllocAct(int);
void InsertXfAct(SO *, XF *, ACT *);
void func_00130010(ASEG *, ALO *, ASEGPART *, LO **, unsigned *);
PARTLINK *func_0012CE50(int);
void SetAsegaHandsOff(ASEGA *, int);
void HandleAsegaEvent(ASEGA *, ASEGEVENT *);
void SnapAsega(ASEGA *, int);
void HandleAsegaEventsFF(ASEGA *);
void UpdateAsegaIeaCur__FP5ASEGA(ASEGA *);
}
extern "C" void ApplyAseg(ASEG *paseg, ALO *paloRoot, float tLocal, float svtLocal, int grfapl, ASEGA **ppasega)
{
    ASEGA *pasega = (ASEGA *)PvAllocSlotheapImpl(&B_003E1224);
    memset(pasega, 0, 0x60);
    pasega->pframe = 0;
    pasega->psidebag = 0;
    ((ASEGAVTABLE *)pasega)->vtable = D_002CAF48;
    pasega->field_0x5C = 0;
    pasega->paseg = paseg;
    pasega->paloRoot = paloRoot;
    pasega->tLocal = tLocal;
    pasega->grfapl = grfapl;
    pasega->svtMaster = paseg->svtMaster;
    float suck = GetSuck(B_002DE578);
    pasega->factor = GLimitLm(&paseg->lmSpeed, GFromClq(&paseg->clqSpeed, suck));
    SetAsegaSpeed(pasega, svtLocal);
    AppendDlEntry(&B_003E1218, pasega);
    AppendDlEntry(&paseg->dlAsega, pasega);
    pasega->OnAdd();
    ASEGALOCK lock(pasega);
    CFramePtr_Assign(pasega, paseg->pframe);
    if (ppasega)
        *ppasega = pasega;
    int ichn = 0;
    if (ichn < paseg->cchn) {
        do {
            ASEGCHN *pchn = &paseg->achn[ichn];
            if (pchn->grf & 0x40000000)
                goto next;
            SO *pso;
            XF *pxf;
            BindAsegChn(paseg, paloRoot, pchn, &pso, &pxf);
            if (pxf) {
                func_001F8668(pso, 0);
                ACTASEG *pact = (ACTASEG *)PvAllocAct(0x2C);
                pact->act.vtable = D_002CAF08;
                pact->act.kind = 0;
                if (pchn->grf & 0x80000000)
                    pact->panimAlt = pchn->panim;
                else
                    pact->panim = pchn->panim;
                pact->act.palo = (ALO *)pso;
                pact->act.pxf = pxf;
                pact->act.priority = paseg->priorityAct;
                pact->act.xfk = (grfapl & 1) ? 7 : 5;
                pact->pasega = pasega;
                pact->pactNext = pasega->pactFirst;
                pasega->pactFirst = pact;
                InsertXfAct(pso, pxf, &pact->act);
            }
        next:;
        } while (++ichn < paseg->cchn);
    }
    for (int ipart = 0; ipart < paseg->cpart; ipart++) {
        ASEGPART *ppart = &paseg->apart[ipart];
        LO *plo;
        unsigned nTarget;
        func_00130010(paseg, paloRoot, ppart, &plo, &nTarget);
        if (nTarget) {
            PARTLINK *plink = func_0012CE50(0x14);
            plink->psink = ppart->psink;
            plink->nTarget = nTarget;
            plink->plo = plo;
            plink->ipart = ppart->ipart;
            plink->pnext = pasega->plink;
            pasega->plink = plink;
            plo->Slot44(ppart->ipart);
        }
    }
    SetAsegaHandsOff(pasega, paseg->handsOff);
    pasega->tTarget = tLocal;
    for (int ievent = 0; ievent < paseg->cevent; ievent++)
        HandleAsegaEvent(pasega, &paseg->aevent[ievent]);
    pasega->tLocal = pasega->tTarget;
    SnapAsega(pasega, (grfapl >> 2) & 1);
    if (grfapl & 2) {
        if (pasega->svtLocal < 0.0f)
            pasega->iea = paseg->iea;
        HandleAsegaEventsFF(pasega);
    } else
        UpdateAsegaIeaCur__FP5ASEGA(pasega);
    pasega->HandleSpliceEvent(2, 0, 0, 0, 0);
}
