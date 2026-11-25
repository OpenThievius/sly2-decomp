#include "sly2.h"
#include "stepguard.h"
#include "goal.h"
struct GOAL_17D188 : GOAL {
    u8 unknown_0x30[0x8];
    float z;
};
int func_0017D188(GOAL_17D188 *pgoal)
{
    float diff = ((STEPGUARD *)pgoal->pstep)->sPath - pgoal->z;
    int result = 1;
    if (__builtin_fabsf(diff) < 50.0f) {
    } else
        result = 0;
    return result;
}
