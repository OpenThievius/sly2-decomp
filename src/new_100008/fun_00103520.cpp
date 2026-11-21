#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void AddGuardPriorityClass(void *, int);

CRef func_00103520(void *self, int count, CRef *args)
{
    int aotyp[1];
    int value;
    aotyp[0] = 0x7;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    AddGuardPriorityClass(self, value);
    return ref;
}
