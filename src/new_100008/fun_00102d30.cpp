#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int v[5]; };
extern "C" void func_00207CF8(BASIC *, CRef *, int, int, int, int);
extern const AOT RO_002A3B30;

CRef func_00102D30(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3B30;
    CRef crefArg;
    crefArg.m_tagk = TAGK_Nil;
    int oid0, oid1, oid2, oid3;
    RefSetArgsFromSplice(5, args, &aotyp, &crefArg, &oid0, &oid1, &oid2, &oid3);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00207CF8(object, &crefArg, oid0, oid1, oid2, oid3);
    return refResult;
}
