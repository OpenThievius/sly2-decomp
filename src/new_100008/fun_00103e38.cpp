#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void func_00171D58(void *, int);

extern "C" CRef func_00103E38(void *self, int count, CRef *args)
{
    int aotyp[1] = {0x2071};
    int value;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_00171D58(self, value);
    return refResult;
}
