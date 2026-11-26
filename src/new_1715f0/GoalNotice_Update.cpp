#include "types.h"
#include "ps2inline.h"
#include "vu0inline.h"

#include "stepguard.h"
#include "goals.h"
#include "phys.h"
#include "pathzone.h"

struct LINK { u8 unknown_0x0[0x10]; PATHZONE *zone; }; /* the region link of a PHYS: only the zone is read here, as its other readers do */
/* what STEPGUARD::field_0xFC4 points at: only its divisor at 0x20 is read, here */
struct DIVISOR { u8 unknown_0x0[0x20]; float gDivisor; };
struct TARGET { int a[4]; QW pos; };

extern "C" {
void func_001EEF98(GOALNOTICE *);
int func_001EF0A8(GOALNOTICE *);
int func_00209098(STEPGUARD *);
int func_00176060(GOALNOTICE *);
int func_00175FF0(GOALNOTICE *);
int func_00175D00(GOALNOTICE *);
void GoalNotice_SetState(GOALNOTICE *, int);
QW PosLoWorld(void *);
PATHZONE *PpathzoneFindPos(QW, int);
void func_002562A8(TARGET *);
void SetGoalTarget(GOAL *, TARGET *);
int FGoalReactDone(GOAL *);
int FGoalAnimDone(GOAL *);
int func_0017B7F8(GOAL *);
void func_0020B140(STEPGUARD *, void *);
}
extern float D_FLT_002BE614;
extern float g_2dded0;
extern float B_FLT_003E1BE8;

static inline PATHZONE *ZoneOf(STEPGUARD *pstep)
{
    PHYS *pphys = pstep->pphys;
    LINK *plink = 0;
    if (pphys != 0)
        plink = pphys->plink;
    PATHZONE *pzone = 0;
    if (plink != 0)
        pzone = plink->zone;
    return pzone;
}

static inline int FMoved(QW current, QW last)
{
    return D_FLT_002BE614 < LaneX(SqrtX(SquaredLength(VectorSub(current, last))));
}

extern "C" void GoalNotice_Update(GOALNOTICE *pgoal)
{
    TARGET target;
    func_001EEF98(pgoal);
    int state;
    do {
        state = pgoal->state;
        switch (state) {
        case 0:
        case 3:
            if (func_001EF0A8(pgoal) == 0) {
                if (func_00209098((STEPGUARD *)pgoal->pstep) != 0) {
                    GoalNotice_SetState(pgoal, 5);
                } else if (func_00176060(pgoal) != 0) {
                    GoalNotice_SetState(pgoal, 4);
                } else if (func_00175FF0(pgoal) != 0) {
                    GoalNotice_SetState(pgoal, 1);
                } else if (func_00175D00(pgoal) != 0) {
                    GoalNotice_SetState(pgoal, 2);
                } else {
                    QW pos = PosLoWorld(pgoal->ptarget);
                    QW posStep = PosLoWorld(pgoal->pstep);
                    float distance = LaneX(SqrtX(SquaredLengthXy(VectorSub(pos, posStep))));
                    if (((STEPGUARD *)pgoal->pstep)->mode == 8 || ((STEPGUARD *)pgoal->pstep)->mode == 13) {
                        if (((STEPGUARD *)pgoal->pstep)->field_0xFC4 != 0)
                            distance /= ((DIVISOR *)((STEPGUARD *)pgoal->pstep)->field_0xFC4)->gDivisor;
                    }
                    PATHZONE *pzone = PpathzoneFindPos(pos, 1);
                    if (pgoal->state != 0) {
                        if (pgoal->state == 3) {
                            STEPGUARD *pstepFar = (STEPGUARD *)pgoal->pstep;
                            if (distance < pstepFar->gNear && pzone == ZoneOf(pstepFar)) {
                                GoalNotice_SetState(pgoal, 0);
                            } else if (pgoal->pzone != pzone || FMoved(pos, pgoal->posLast)) {
                                pgoal->pzone = pzone;
                                pgoal->posLast = pos;
                                func_002562A8(&target);
                                target.pos = pos;
                                SetGoalTarget(pgoal->pgoalChild, &target);
                            }
                        }
                    } else {
                        STEPGUARD *pstepNear = (STEPGUARD *)pgoal->pstep;
                        if (pstepNear->gFar < distance || pzone != ZoneOf(pstepNear))
                            GoalNotice_SetState(pgoal, 3);
                    }
                }
            }
            break;
        case 1:
            if (func_00209098((STEPGUARD *)pgoal->pstep) != 0) {
                GoalNotice_SetState(pgoal, 5);
            } else if (func_001EF0A8(pgoal) == 0) {
                if (FGoalReactDone(pgoal->pgoalChild) != 0)
                    GoalNotice_SetState(pgoal, 0);
            }
            break;
        case 2:
            if (func_00209098((STEPGUARD *)pgoal->pstep) != 0) {
                GoalNotice_SetState(pgoal, 5);
            } else if (func_001EF0A8(pgoal) == 0) {
                if (func_0017B7F8(pgoal->pgoalChild) != 0)
                    GoalNotice_SetState(pgoal, 0);
            }
            break;
        case 4:
            if (func_001EF0A8(pgoal) == 0 && FGoalAnimDone(pgoal->pgoalChild) != 0)
                GoalNotice_SetState(pgoal, -1);
            break;
        case 5:
            if (func_001EF0A8(pgoal) == 0 && func_00209098((STEPGUARD *)pgoal->pstep) == 0)
                GoalNotice_SetState(pgoal, 3);
            break;
        }
    } while (state != pgoal->state);
    STEPGUARD *pstepEnd = (STEPGUARD *)pgoal->pstep;
    if (pstepEnd->fActive != 0 && state < 4 && state >= 0 && pstepEnd->tMin <= g_2dded0 && B_FLT_003E1BE8 <= g_2dded0)
        func_0020B140(pstepEnd, pgoal->ptarget);
}
