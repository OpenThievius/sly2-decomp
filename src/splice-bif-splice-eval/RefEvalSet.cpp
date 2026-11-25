#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);
extern "C" CRef RefSetBinding__6CFrameUiP4CRef(CFrame *, int, CRef *);

extern "C" CRef RefEvalSet(CPair *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *ppairSymbol = ppair->ref.m_tag.m_ppair->next;
    refResult = RefEval(ppairSymbol->next, pframe);
    refResult = RefSetBinding__6CFrameUiP4CRef(pframe, ppairSymbol->ref.m_tag.m_symid, &refResult);
    return refResult;
}
