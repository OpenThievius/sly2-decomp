#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);

extern "C" CRef RefEvalIf__FP5CPairP6CFrame(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *ppairTest = ppair->ref.m_tag.m_ppair->next;
    CPair *ppairThen = ppairTest->next;
    CPair *ppairElse = ppairThen->next;
    refResult = RefEval(ppairTest, pframe);
    if (refResult.m_tag.m_n == 1) {
        refResult = RefEval(ppairThen, pframe);
    } else if (ppairElse != 0) {
        refResult = RefEval(ppairElse, pframe);
    } else {
        refResult.Decref();
        refResult.SetTag(TAGK_Void);
    }
    return refResult;
}
