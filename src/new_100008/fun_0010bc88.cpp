#include "sly2.h"
#include "cref.h"
#include "po.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct AOT { int v[1]; };

CRef func_0010BC88(PO *object, int count, CRef *args)
{
    AOT aotyp;
    aotyp.v[0] = 0x1011;
    int arg;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &arg);
    int value = object->FInvulnerable(arg);
    refResult.SetBool(value != 0);
    return refResult;
}
