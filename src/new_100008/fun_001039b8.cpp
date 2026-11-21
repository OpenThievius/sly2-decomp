#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void RemoveGuardClassFilter(void *, int);

extern "C" CRef func_001039B8(void *self, int count, CRef *args)
{
    int aotyp[1] = {0x7};
    int value;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    RemoveGuardClassFilter(self, value);
    return refResult;
}
