#include "sly2.h"
struct Pair { int pad0; int pad4; int tagk; Pair *pv; Pair *next; };
struct Frame;
struct Proc { int cref; int pad4; Frame *pframe; int crefReq; int fVarArg; Pair *formals; Pair *code; };
struct Ref { int a; };
extern "C" {
Proc *PprocNew(void);
void func_00257038(Proc **h, Proc *p);
void CFramePtr_Assign(void *h, Frame *f);
void PairHandle_Assign(void *h, Pair *p);
void CRef_ConstructProc(Ref *r, Proc *p);
void CProc_DeletingDestructor(Proc *p, int f);
}
Ref *RefEvalLambda(Ref *ret, Pair *pair, Frame *frame)
{
    Pair *formals = pair->pv->next;
    Pair *code = formals->next;
    Proc *h;
    func_00257038(&h, PprocNew());
    CFramePtr_Assign(&h->pframe, frame);
    if (formals->tagk == 0)
        PairHandle_Assign(&h->formals, 0);
    else
        PairHandle_Assign(&h->formals, formals->pv);
    PairHandle_Assign(&h->code, code);
    int vararg = 0;
    int req = 0;
    Pair *p = h->formals;
    while (p) {
        if (p->tagk == 0x14) { vararg = 1; p = 0; }
        else { p = p->next; req++; }
    }
    h->crefReq = req;
    h->fVarArg = vararg;
    CRef_ConstructProc(ret, h);
    Proc *t = h;
    if (t && --t->cref == 0)
        CProc_DeletingDestructor(t, 3);
    return ret;
}
