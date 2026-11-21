#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int v[3]; };
extern "C" void UseGuardAnimationImmediate(BASIC *, CRef *, int, int);
extern const AOT RO_002A3B20;

CRef RefCallUseGuardAnimationImmediate(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3B20;
    CRef crefArg;
    crefArg.m_tagk = TAGK_Nil;
    int a, b;
    RefSetArgsFromSplice(3, args, &aotyp, &crefArg, &a, &b);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    UseGuardAnimationImmediate(object, &crefArg, a, b);
    return refResult;
}
