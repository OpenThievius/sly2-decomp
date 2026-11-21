#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
extern "C" void SetHubAllowedStates(BASIC *, CRef *);
CRef RefSetHubAllowedStates(BASIC *object, int count, CRef *args)
{
    int aotyp = 0x8006;
    CRef states;
    states.m_tagk = TAGK_Nil;
    RefSetArgsFromSplice(1, args, &aotyp, &states);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetHubAllowedStates(object, &states);
    return refResult;
}
