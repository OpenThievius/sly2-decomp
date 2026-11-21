#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void RemoveGuardPriorityClass(void *, int);

CRef func_001035A8(void *self, int count, CRef *args)
{
    int aotyp[1];
    int value;
    aotyp[0] = 0x7;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    RemoveGuardPriorityClass(self, value);
    return ref;
}
