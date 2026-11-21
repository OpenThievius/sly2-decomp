#include "sly2.h"
#include "cref.h"
struct CPair { char pad[0x10]; CPair *next; };
struct CProc { char pad[0x18]; CPair *code; };
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
