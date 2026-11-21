#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void AddGuardSensedObject_thunk(void *, int);

CRef func_00103498(void *self, int count, CRef *args)
{
    int aotyp[1];
    int value;
    aotyp[0] = 0x2002;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    AddGuardSensedObject_thunk(self, value);
    return ref;
}
