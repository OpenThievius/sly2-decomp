#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void AddGuardAimOidResolve(void *, int);

CRef RefCallAddGuardAimOidResolve(void *self, int count, CRef *args)
{
    int aotyp[1];
    int value;
    aotyp[0] = 0x6;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    AddGuardAimOidResolve(self, value);
    return ref;
}
