#include "sly2.h"
#include "cref.h"
struct CPair2 { char pad[0xC]; int sym; int expr; };
struct CPair1 { char pad[0x10]; CPair2 *next; };
struct CPair0 { char pad[0xC]; CPair1 *next; };
struct CFrame;
extern "C" CRef RefEval(int, CFrame *);
extern "C" CRef RefSetBinding__6CFrameUiP4CRef(CFrame *, int, CRef *);

extern "C" CRef RefEvalSet(CPair0 *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair2 *ppairSymbol = ppair->next->next;
    refResult = RefEval(ppairSymbol->expr, pframe);
    refResult = RefSetBinding__6CFrameUiP4CRef(pframe, ppairSymbol->sym, &refResult);
    return refResult;
}
