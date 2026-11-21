#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
extern "C" int SetBlotLabelListFromRef(BASIC *, CRef *);
CRef RefCallSetBlotLabelListFromRef(BASIC *object, int count, CRef *args)
{
    int aotyp[1] = {0x8010};
    CRef crefArg;
    crefArg.m_tagk = TAGK_Nil;
    RefSetArgsFromSplice(1, args, aotyp, &crefArg);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetBlotLabelListFromRef(object, &crefArg);
    return refResult;
}
