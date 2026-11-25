#include "sly2.h"
struct BRAINDATA { u8 unknown_0x0[0x28]; u64 flags; };
struct ACTOR { u8 unknown_0x0[0xF68]; BRAINDATA *pdata; };
struct GOALBRAIN { u8 unknown_0x0[0x10]; ACTOR *pactor; };
u64 GoalBrain_FGotoTargetInWorld(GOALBRAIN *pbrain)
{
    BRAINDATA *pdata = pbrain->pactor->pdata;
    u64 result = 0;
    if (pdata)
        result = (pdata->flags >> 60) & 1;
    return result;
}
