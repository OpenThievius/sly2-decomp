#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
extern "C" {
extern char B_003DD490;
void func_00174950(GOALFLINCH *);
void GoalFlinch_SetState(GOALFLINCH *, int);
void ResetSensorStates(int);
QW PosLoWorld(char *);
void ReplaceSwHitFx(char *, int, QW, char *, char *);
void func_0017A4E8(GOALFLINCH *goal) {
    func_00174950(goal);
    GoalFlinch_SetState(goal, 0);
    ResetSensorStates((int)GOAL_GUARD(goal)->psensor);
    ReplaceSwHitFx(&B_003DD490, 1, PosLoWorld((char *)GOAL_GUARD(goal)), (char *)GOAL_GUARD(goal), (char *)&GOAL_GUARD(goal)->phitfx);
}
}
