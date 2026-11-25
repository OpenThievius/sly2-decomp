// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goal.h"
struct GOAL_1750E0 : GOAL {
    u8 unknown_0x30[0x8];
    int field_38;
    int field_3c;
    void *panim;
};
extern "C" int GoalAnim_FHandleMessage(GOAL_1750E0 *, int, int *);
extern "C" void SetXfKind(STEPGUARD *, XF *, int);
extern "C" int func_00209518(void *);
int func_001750E0(GOAL_1750E0 *pgoal, int nMsg, int *pmsg)
{
    if (nMsg == 9 && pgoal->panim != 0 && func_00209518(pgoal->panim) == pmsg[0]) {
        switch (pmsg[2]) {
        case 0x29:
            ((STEPGUARD *)pgoal->pstep)->fLock = 1;
            SetXfKind(((STEPGUARD *)pgoal->pstep), ((STEPGUARD *)pgoal->pstep)->pxfAngular, 2);
            return 1;
        case 0x2a:
            ((STEPGUARD *)pgoal->pstep)->fLock = 0;
            if (pgoal->field_38 == 0)
                SetXfKind(((STEPGUARD *)pgoal->pstep), ((STEPGUARD *)pgoal->pstep)->pxfAngular, 1);
            return 1;
        }
    }
    return GoalAnim_FHandleMessage(pgoal, nMsg, pmsg);
}
