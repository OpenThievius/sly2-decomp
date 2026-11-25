#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);

extern "C" CRef RefEvalBegin(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    refResult.Decref();
    refResult.SetTag(TAGK_Void);
    for (CPair *ppairExpr = ppair->ref.m_tag.m_ppair->next; ppairExpr != 0; ppairExpr = ppairExpr->next) {
        refResult = RefEval(ppairExpr, pframe);
    }
    return refResult;
}
