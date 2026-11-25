#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);

extern "C" CRef RefEvalWhile__FP5CPairP6CFrame(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *ppairTest = ppair->ref.m_tag.m_ppair->next;
    CPair *ppairBody = ppairTest->next;
    while (1) {
        refResult = RefEval(ppairTest, pframe);
        if (refResult.m_tagk == TAGK_Bool && refResult.m_tag.m_bool == 0)
            break;
        refResult = RefEval(ppairBody, pframe);
    }
    refResult.Decref();
    refResult.SetTag(TAGK_Void);
    return refResult;
}
