#include "sly2.h"
#include "cref.h"
struct CPair2 { char pad[0x10]; CPair2 *next; };
struct CPair0 { char pad[0xC]; CPair2 *pv; };
struct CFrame;
extern "C" CRef RefEval(CPair2 *, CFrame *);

extern "C" CRef RefEvalAnd__FP5CPairP6CFrame(CPair0 *ppair, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    refResult.SetBool(1);
    CPair2 *ppairOperand = ppair->pv->next;
    while (ppairOperand != 0) {
        refResult = RefEval(ppairOperand, pframe);
        if (refResult.m_tagk == TAGK_Bool && refResult.m_tag.m_bool == 0)
            return refResult;
        ppairOperand = ppairOperand->next;
    }
    return refResult;
}
