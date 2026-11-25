#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);

extern "C" CRef RefEvalOr__FP5CPairP6CFrame(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *ppairOperand = ppair->ref.m_tag.m_ppair->next;
    while (ppairOperand != 0) {
        refResult = RefEval(ppairOperand, pframe);
        if (refResult.m_tagk != TAGK_Bool || refResult.m_tag.m_bool != 0)
            return refResult;
        ppairOperand = ppairOperand->next;
    }
    refResult.SetBool(0);
    return refResult;
}
