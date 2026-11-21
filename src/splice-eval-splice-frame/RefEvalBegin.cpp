#include "sly2.h"
#include "cref.h"
struct CPair { char pad[0x10]; CPair *next; };
struct CPairHead { char pad[0x10]; CPair *next; };
struct CPair0 { char pad[0xC]; CPairHead *head; };
struct CFrame;
extern "C" CRef RefEval(CPair *, CFrame *);

extern "C" CRef RefEvalBegin(CPair0 *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    refResult.Decref();
    refResult.SetTag(TAGK_Void);
    for (CPair *ppairExpr = ppair->head->next; ppairExpr != 0; ppairExpr = ppairExpr->next) {
        refResult = RefEval(ppairExpr, pframe);
    }
    return refResult;
}
