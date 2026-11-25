#include "button.h"
#include "sly2.h"
#include "sw.h"

extern "C" {
void FAddRsmg__FP4RSMGiPii3OIDN24(const void *, RSMG *, int, int *, int, int, int, int);
extern SW B_003DD490;
}

void SetAlarmRsmg__FP5ALARMi3OIDN22(BTN *pbtn, int fOnTrigger, int oidRoot, int oidSM, int oidGoal)
{
    FAddRsmg__FP4RSMGiPii3OIDN24(&B_003DD490, pbtn->arsmg, 8, &pbtn->crsmg, fOnTrigger, oidRoot, oidSM, oidGoal);
}
