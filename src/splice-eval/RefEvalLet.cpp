#include "sly2.h"
#include "cref.h"
struct P { int pad0; int pad4; int tagk; P *pv; P *next; };
struct CFrame { int refs; };
extern "C" void CFrame_DeletingDestructor(CFrame *, int);
struct CFramePtr {
    CFrame *p; int pad[3];
    ~CFramePtr() {
        CFrame *pf = p;
        if (pf != 0) {
            int refs = pf->refs - 1;
            pf->refs = refs;
            if (refs == 0)
                CFrame_DeletingDestructor(pf, 3);
        }
    }
};
extern "C" CRef RefEval(P *, CFrame *);
extern "C" CFrame *PframeNew();
extern "C" void CFramePtr_Assign(CFramePtr *, CFrame *);
extern "C" CRef CFrame_RefAddBinding(CFrame *, int, CRef *);
extern "C" void bevy_splice_frame_set_parent(CFrame *, CFrame *);
extern "C" CRef RefEvalLet(P *ppair, CFrame *pframe)
{
    CRef refResult;
    CRef refInit;
    CRef refBinding;
    CFramePtr pframeLet;
    pframeLet.p = 0;
    refResult.m_tagk = TAGK_Nil;
    refInit.m_tagk = TAGK_Nil;
    refBinding.m_tagk = TAGK_Nil;
    P *pbindings = ppair->pv->next;
    if (pbindings->tagk == TAGK_Pair) {
        CFrame *pnew = PframeNew();
        CFramePtr_Assign(&pframeLet, pnew);
        for (P *pentry = pbindings->pv; pentry != 0; pentry = pentry->next) {
            P *psym = pentry->pv;
            refInit = RefEval(psym->next, pframe);
            refBinding = CFrame_RefAddBinding(pframeLet.p, (sptr)psym->pv, &refInit);
        }
        bevy_splice_frame_set_parent(pframeLet.p, pframe);
    } else {
        CFramePtr_Assign(&pframeLet, pframe);
    }
    P *pnode = pbindings->next;
    if (pnode != 0) {
        do {
            refResult = RefEval(pnode, pframeLet.p);
            pnode = pnode->next;
        } while (pnode != 0);
    }
    return refResult;
}
