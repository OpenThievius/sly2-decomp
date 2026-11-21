#include "sly2.h"
#include "cref.h"
struct CPair2 { char pad[0x10]; CPair2 *next; };
struct CPair0 { char pad[0xC]; CPair2 *pv; };
struct CFrame;
extern "C" CRef RefEval(CPair2 *, CFrame *);

extern "C" CRef RefEvalWhile__FP5CPairP6CFrame(CPair0 *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    CPair2 *ppairTest = ppair->pv->next;
    CPair2 *ppairBody = ppairTest->next;
    while (1) {
        refResult = RefEval(ppairTest, pframe);
        if (refResult.m_tagk == TAGK_Bool && refResult.m_tag.m_bool == 0)
            break;
        refResult = RefEval(ppairBody, pframe);
    }
    refResult.Decref();
    refResult.SetTag(TAGK_Void);
    return refResult;
}
