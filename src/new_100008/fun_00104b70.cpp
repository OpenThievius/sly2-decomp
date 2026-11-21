#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void SnapSmaToGoal(void *, int);

extern "C" CRef func_00104B70(void *self, int count, CRef *args)
{
    int aotyp[1] = {0x6};
    int value;
    RefSetArgsFromSplice(1, args, aotyp, &value);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SnapSmaToGoal(self, value);
    return refResult;
}
