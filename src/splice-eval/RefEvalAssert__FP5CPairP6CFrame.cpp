#include "sly2.h"
#include "cref.h"
struct CPair { int count; int pad4; CRef ref; CPair *next; };
struct CFrame;
extern "C" {
CRef RefEval(CPair *, CFrame *);
CRef RefOpPrint(int, CRef *, CFrame *);
int printf(const char *, ...);
}

extern "C" CRef RefEvalAssert__FP5CPairP6CFrame(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *pexpr = ((CPair *)ppair->ref.m_tag.m_n)->next;
    CPair *pmessage = pexpr->next;
    refResult = RefEval(pexpr, pframe);
    if (refResult.m_tag.m_n == 0) {
        CPair *pmessageNext = ((CPair *)pmessage->ref.m_tag.m_n)->next;
        printf("Splice assert: ");
        RefOpPrint(1, &pmessageNext->ref, pframe);
    }
    refResult.Decref();
    refResult.SetTag(TAGK_Void);
    return refResult;
}
