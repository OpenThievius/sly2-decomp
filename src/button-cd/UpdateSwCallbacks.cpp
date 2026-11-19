#include "sly2.h"
#include "types.h"
#include "cref.h"
#include "timedcall.h"
struct B8 { char b[8]; };
struct OBJ { virtual void v0(); int pad; };
typedef void (OBJ::*PMF)(int);
struct CB { OBJ *plo; B8 pmf; int nArg; CB *pnext; };
#include "sw.h"
struct CFrame { int refs; };
struct OWNER { CFrame *pframe; };
extern "C" {
int FIsSlEmpty(void *);
void ClearSl(void *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void RemoveSlEntry(void *, void *);
CFrame *PframeNew(void);
void func_00257058(CFrame **, CFrame *);
void EvalScriptCall(void *, CPair *, CFrame *, CRef *);
void CFrame_DeletingDestructor(CFrame *, int);
void CPairPtr_Destructor(CPair **, int);
void CRef_Destruct(CRef *);
void UnlinkPairNode(CPair *);
extern SLOTHEAP B_004520A8;
extern float g_2dded0;
}
struct CFramePtr {
    CFrame *pframe;
    CFramePtr() {}
    CFramePtr(const CFramePtr &);
    ~CFramePtr()
    {
        CFrame *pframeOld = pframe;
        if (pframeOld != 0) {
            if (--pframeOld->refs == 0)
                CFrame_DeletingDestructor(pframeOld, 3);
        }
    }
};
extern "C" void UpdateSwCallbacks(SW *psw)
{
    while (!FIsSlEmpty(&psw->pcbFirst)) {
        CB *pcb = psw->pcbFirst;
        ClearSl(&psw->pcbFirst);
        for (; pcb != 0; ) {
            PMF pmf;
            *(B8 *)&pmf = pcb->pmf;
            (pcb->plo->*pmf)(pcb->nArg);
            CB *pnext = pcb->pnext;
            FreeSlotheapPv(&psw->slotheapCb, pcb);
            pcb = pnext;
        }
    }
    for (;;) {
        TIMEDCALL *pcall = psw->ptimedcallFirst;
        if (pcall == 0 || g_2dded0 < pcall->tFire)
            break;
        OWNER *powner = (OWNER *)pcall->powner;
        pcall->idCall = -1;
        if (powner != 0) {
            EvalScriptCall(powner, pcall->ppair, powner->pframe, 0);
        } else {
            CFramePtr frame;
            func_00257058(&frame.pframe, PframeNew());
            EvalScriptCall(psw, pcall->ppair, frame.pframe, 0);
        }
        RemoveSlEntry(&psw->ptimedcallFirst, pcall);
        CPair *ppair = pcall->ppair;
        if (--ppair->cref == 0 && ppair != 0) {
            CPairPtr_Destructor(&ppair->next, 2);
            CRef_Destruct(&ppair->ref);
            UnlinkPairNode(ppair);
            FreeSlotheapPv(&B_004520A8, ppair);
        }
        FreeSlotheapPv(&psw->slotheapTimedcall, pcall);
    }
}
