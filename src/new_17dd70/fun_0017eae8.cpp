#include "stepguard.h"
#include "goals.h"
extern "C" int FGoalAnimDone(void *);
extern "C" int func_001C1FA0(void *, float, void *);

/* GoalSnapToPoint's done function (between its Snap, func_0017E9B0, and GoalFollowCurve's Init). */
int func_0017EAE8(GOALSNAPTOPOINT *arg0) {
    if ((GOAL_GUARD(arg0)->grf & 1) != 0) {
        if (FGoalAnimDone(arg0->pgoalChild) == 0) {
            return 0;
        }
    }
    return func_001C1FA0(&arg0->target, 25.0f, GOAL_GUARD(arg0));
}
