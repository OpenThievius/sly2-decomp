#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);
extern "C" CRef CFrame_RefAddBinding(CFrame *, int, CRef *);

extern "C" CRef RefEvalDefine(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *ppairSymbol = ppair->ref.m_tag.m_ppair->next;
    refResult = RefEval(ppairSymbol->next, pframe);
    refResult = CFrame_RefAddBinding(pframe, ppairSymbol->ref.m_tag.m_symid, &refResult);
    return refResult;
}
