#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
u64 GoalBrain_FGotoTargetInWorld(GOALBRAIN *pbrain)
{
    LO *ptarget = ((STEPGUARD *)pbrain->pstep)->ptargetGoto;
    u64 result = 0;
    if (ptarget)
        result = (ptarget->grfo >> 60) & 1;
    return result;
}
