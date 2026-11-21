#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void JoltCm(void *, int);

CRef RefCallJoltCm(void *self, int count, CRef *args)
{
    int aotyp[1];
    int value;
    aotyp[0] = 0x1004;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    JoltCm(self, value);
    return ref;
}
