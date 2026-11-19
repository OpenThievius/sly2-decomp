#include "types.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "stepguard.h"
#include "goal.h"
struct SEARCHBEH : GOAL {
    int state;
    char pad34[4];
    float tRetarget;
    float tSwitch;
    char pad40[8];
    int fRequest;
};
struct TARGET {
    int a[4];
    QW pos;
};
extern "C" {
void func_001EEF98(SEARCHBEH *);
int func_001EF0A8(SEARCHBEH *);
int FGoalAnimDone(GOAL *);
int func_00209098(STEP *);
void func_00209818(void *, float);
int func_00172658(SEARCHBEH *);
QW func_00172760(SEARCHBEH *);
void func_00172560(SEARCHBEH *);
void func_00172F10(SEARCHBEH *);
void func_002562A8(TARGET *);
void SetGoalTarget(GOAL *, TARGET *);
int GoalGoto_FArrived(GOAL *);
int GoalGoto_FBlocked(GOAL *);
void SetSearchState(SEARCHBEH *, int);
QW PosLoWorld(STEP *);
float atan2f(float, float);
extern float g_2dded0;
}

extern "C" void UpdateSearchBeh(SEARCHBEH *pbeh)
{
    func_001EEF98(pbeh);
    while (!func_001EF0A8(pbeh)) {
        int state = pbeh->state;
        switch (state) {
        case 0:
            if (FGoalAnimDone(pbeh->pgoalChild))
                SetSearchState(pbeh, 1);
            break;
        case 1:
            if (func_00209098(pbeh->pstep)) {
                SetSearchState(pbeh, 5);
            } else if (pbeh->fRequest) {
                if (func_00172658(pbeh)) {
                    SetSearchState(pbeh, 2);
                } else {
                    QW target = func_00172760(pbeh);
                    TARGET goal;
                    func_002562A8(&goal);
                    goal.pos = target;
                    SetGoalTarget(pbeh->pgoalChild, &goal);
                }
                pbeh->fRequest = 0;
            } else if (func_00172658(pbeh) || GoalGoto_FArrived(pbeh->pgoalChild) || GoalGoto_FBlocked(pbeh->pgoalChild)) {
                SetSearchState(pbeh, 2);
            }
            break;
        case 2:
            if (func_00209098(pbeh->pstep)) {
                SetSearchState(pbeh, 5);
            } else if (pbeh->fRequest) {
                if (func_00172658(pbeh))
                    func_00172560(pbeh);
                else
                    SetSearchState(pbeh, 1);
                pbeh->fRequest = 0;
            } else if (pbeh->tRetarget < g_2dded0 || FGoalAnimDone(pbeh->pgoalChild)) {
                SetSearchState(pbeh, 4);
            } else if (pbeh->tSwitch < g_2dded0) {
                SetSearchState(pbeh, 3);
            } else {
                QW offset = VectorSub(func_00172760(pbeh), PosLoWorld(pbeh->pstep));
                void *pxps = &((STEPGUARD *)pbeh->pstep)->field_0xFD0;
                func_00209818(pxps, atan2f(LaneYInGeneralRegister(offset), LaneX(offset)));
            }
            break;
        case 3:
            if (func_00209098(pbeh->pstep)) {
                SetSearchState(pbeh, 5);
            } else if (pbeh->fRequest) {
                if (func_00172658(pbeh))
                    SetSearchState(pbeh, 2);
                else
                    SetSearchState(pbeh, 1);
                pbeh->fRequest = 0;
            } else if (pbeh->tRetarget < g_2dded0) {
                SetSearchState(pbeh, 4);
            } else {
                func_00172F10(pbeh);
            }
            break;
        case 5:
            if (!func_00209098(pbeh->pstep))
                SetSearchState(pbeh, 1);
            break;
        case 4:
            if (pbeh->fRequest) {
                if (func_00172658(pbeh))
                    SetSearchState(pbeh, 2);
                else
                    SetSearchState(pbeh, 1);
                pbeh->fRequest = 0;
            } else if (FGoalAnimDone(pbeh->pgoalChild)) {
                SetSearchState(pbeh, -1);
            }
            break;
        }
        if (pbeh->state == state)
            break;
    }
}
