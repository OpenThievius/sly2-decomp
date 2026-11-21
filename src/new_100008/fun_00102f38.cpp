#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int v[6]; };
extern "C" void func_00207E08(BASIC *, CRef *, int, float, float, float, float);
extern const AOT RO_002A3B48;

CRef func_00102F38(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3B48;
    CRef crefArg;
    crefArg.m_tagk = TAGK_Nil;
    int oid;
    float g0, g1, g2, g3;
    RefSetArgsFromSplice(6, args, &aotyp, &crefArg, &oid, &g0, &g1, &g2, &g3);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00207E08(object, &crefArg, oid, g0, g1, g2, g3);
    return refResult;
}
