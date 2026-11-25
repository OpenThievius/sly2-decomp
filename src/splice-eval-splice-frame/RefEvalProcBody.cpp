#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct CProc { u8 unknown_0x0[0x18]; CPair *code; };
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);

extern "C" CRef RefEvalProcBody(CProc *pproc, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair *ppair = pproc->code;
    do {
        refResult = RefEval(ppair, pframe);
        ppair = ppair->next;
    } while (ppair != 0);
    return refResult;
}
