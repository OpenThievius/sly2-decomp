#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" CRef *CRef_SetBool(CRef *, int);

CRef func_00100A00(LO *object, int count, CRef *args)
{
    int aotyp[1];
    LO *arg;
    aotyp[0] = 0x2002;
    RefSetArgsFromSplice(1, args, aotyp, &arg);
    CRef ref;
    ref.SetTag(TAGK_Void);
    object->SetPosMatFromLo(arg);
    return ref;
}
