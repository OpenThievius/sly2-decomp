#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void AddGuardIgnoredClass(void *, int);

CRef func_001037A8(void *self, int count, CRef *args)
{
    int aotyp[1];
    int value;
    aotyp[0] = 0x7;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    AddGuardIgnoredClass(self, value);
    return ref;
}
