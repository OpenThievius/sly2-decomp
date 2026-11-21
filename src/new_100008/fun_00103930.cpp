#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void AddGuardClassFilter(void *, int);

CRef func_00103930(void *self, int count, CRef *args)
{
    int aotyp[1];
    int value;
    aotyp[0] = 0x7;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    AddGuardClassFilter(self, value);
    return ref;
}
