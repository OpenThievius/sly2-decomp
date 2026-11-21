#include "sly2.h"
#include "cref.h"
struct CPair2 { char pad[0x10]; CPair2 *next; };
struct CPair0 { char pad[0xC]; CPair2 *pv; };
struct CFrame;
extern "C" CRef RefEval(CPair2 *, CFrame *);

extern "C" CRef func_001266C8(CPair0 *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair2 *ppairTest = ppair->pv->next;
    if (ppairTest != 0) {
        refResult = RefEval(ppairTest, pframe);
    } else {
        refResult.Decref();
        refResult.SetTag(TAGK_Void);
    }
    return refResult;
}
