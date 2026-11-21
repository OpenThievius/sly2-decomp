#include "sly2.h"
#include "cref.h"
struct CPair2 { char pad[0x10]; CPair2 *next; };
struct CPair0 { char pad[0xC]; CPair2 *pv; };
struct CFrame;
extern "C" CRef RefEval(CPair2 *, CFrame *);

extern "C" CRef RefEvalIf__FP5CPairP6CFrame(CPair0 *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair2 *ppairTest = ppair->pv->next;
    CPair2 *ppairThen = ppairTest->next;
    CPair2 *ppairElse = ppairThen->next;
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
