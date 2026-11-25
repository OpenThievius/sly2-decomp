#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);

extern "C" CRef func_001266C8(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *ppairTest = ppair->ref.m_tag.m_ppair->next;
    if (ppairTest != 0) {
        refResult = RefEval(ppairTest, pframe);
    } else {
        refResult.Decref();
        refResult.SetTag(TAGK_Void);
    }
    return refResult;
}
