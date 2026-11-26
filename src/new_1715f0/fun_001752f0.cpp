#include "types.h"
// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" int GoalAnim_FHandleMessage(GOALTRACK *, int, int *);
extern "C" int func_00209518(void *);
extern "C" void EndJumperFlight(void *);
int func_001752F0(GOALTRACK *pgoal, int nMsg, int *pmsg)
{
    if (nMsg == 9 && pgoal->panimref != 0 && func_00209518(pgoal->panimref) == pmsg[0]) {
        switch (pmsg[2]) {
        case 0x2d:
            ((STEPGUARD *)pgoal->pstep)->fFlag = 1;
            return 1;
        case 0x2e:
            ((STEPGUARD *)pgoal->pstep)->fFlag = 0;
            return 1;
        case 0x30:
            pgoal->fTrackTarget = 0;
            EndJumperFlight(pgoal->panimref->pinst);
            return 1;
        }
    }
    return GoalAnim_FHandleMessage(pgoal, nMsg, pmsg);
}
