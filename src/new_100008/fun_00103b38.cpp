#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int v[2]; };
extern const AOT RO_002A3B70;
extern "C" void SetGuardRefLists(BASIC *, CRef *, CRef *);

CRef func_00103B38(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3B70;
    CRef first;
    first.m_tagk = TAGK_Nil;
    CRef second;
    second.m_tagk = TAGK_Nil;
    RefSetArgsFromSplice(2, args, &aotyp, &first, &second);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetGuardRefLists(object, &first, &second);
    return refResult;
}
