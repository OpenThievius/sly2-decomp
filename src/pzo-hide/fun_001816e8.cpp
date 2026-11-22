// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" int FAddRsmg__FP4RSMGiPii3OIDN24(void *, RSMG *, int, int *, int, int, int, int);
extern SW B_003DD490;

extern "C" void func_001816E8(GRAB *grab, int fOnTrigger, int oidRoot, int oidSM, int oidGoal)
{
    FAddRsmg__FP4RSMGiPii3OIDN24(&B_003DD490, grab->arsmg, 4, &grab->crsmg, fOnTrigger, oidRoot, oidSM, oidGoal);
}
