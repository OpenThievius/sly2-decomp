#include "sly2.h"
#include "goals.h"
extern "C" float D_FLT_002BE62C;
extern "C" float D_FLT_002BE624;
extern "C" float D_FLT_002BE628;
extern "C" void func_001EEF70(void*);
extern "C" QW PosLoWorld(void*);
/* GoalFollowCrv adds slot 15, SetState (goals.h names it in its comment, the header has no virtual for it yet) */
struct GOALFOLLOWCRVSTATE : GOALFOLLOWCRV {
    virtual void SetState(int state);
};
extern "C" void GoalFollowCrv_Activate(GOALFOLLOWCRVSTATE* goal)
{
    func_001EEF70(goal);
    goal->posGoal = PosLoWorld(goal->pstep);
    float radius = goal->field_0x64;
    radius = (radius > D_FLT_002BE62C) ? radius : D_FLT_002BE62C;
    float quarter = radius * 0.25f;
    goal->field_0x64 = radius;
    goal->nearDist = (quarter < D_FLT_002BE624) ? quarter : D_FLT_002BE624;
    goal->farDist = (radius < D_FLT_002BE628) ? radius : D_FLT_002BE628;
    goal->SetState(0);
}
