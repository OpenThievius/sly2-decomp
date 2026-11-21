#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void SetSndbankMasterVolume(void *, float);

CRef RefCallSetSndbankMasterVolume(void *self, int count, CRef *args)
{
    int aotyp[1];
    float value;
    aotyp[0] = 0x1;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef ref;
    ref.SetTag(TAGK_Void);
    SetSndbankMasterVolume(self, value);
    return ref;
}
