// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
struct GUARDSUB : STEPGUARD { int cunk; };
#include "goal.h"
struct GOAL_177BA0 : GOAL {
    int kindRunning;
};
struct CMD { int kind; u8 unknown_0x4[0xC]; int arg; float g; u8 unknown_0x18[0x58]; };
#include "sw.h"
extern SW B_003DD490;
extern "C" {
int FIsBasicDerivedFrom(void *, int);
int PpoSwFocusBase(SW *);
int func_00177D20(GOAL_177BA0 *);
int func_00177D70(GOAL_177BA0 *);
int func_00208B38(void *, void *);
float func_00208BB0(void *);
QW PosLoWorld(void *);
int SpawnSwHitFx(SW *, int, QW, void *);
void GoalBrain_SetCommand(GOAL_177BA0 *, CMD *);
}
void GoalBrain_ChooseNextCommand(GOAL_177BA0 *pgoal)
{
    CMD cmd;
    memset(&cmd, 0, 0x70);
    if (FIsBasicDerivedFrom(((STEPGUARD *)pgoal->pstep), 0x3B) != 0 && ((GUARDSUB *)pgoal->pstep)->cunk > 0) {
        cmd.kind = 0xD;
        cmd.arg = PpoSwFocusBase(&B_003DD490);
    } else if (((STEPGUARD *)pgoal->pstep)->mode == 0x15) {
        cmd.kind = 0x12;
        cmd.arg = PpoSwFocusBase(&B_003DD490);
        cmd.g = 3.4028235e38f;
    } else if (func_00177D20(pgoal) != 0) {
        cmd.kind = 0xC;
    } else if (func_00177D70(pgoal) != 0) {
        cmd.kind = 0xF;
    } else {
        void *target = ((STEPGUARD *)pgoal->pstep)->Slot88();
        if (target != 0) {
            if (func_00208B38(((STEPGUARD *)pgoal->pstep), target) != 0) {
                cmd.kind = 0x12;
                cmd.arg = (sptr)target;
                cmd.g = func_00208BB0(((STEPGUARD *)pgoal->pstep));
            } else {
                cmd.kind = 4;
                cmd.arg = (sptr)target;
            }
        } else {
            int running = pgoal->kindRunning;
            if (running < 0xB) {
                if (running > 5) {
                    cmd.kind = 2;
                    cmd.arg = SpawnSwHitFx(&B_003DD490, 0, PosLoWorld(((STEPGUARD *)pgoal->pstep)), ((STEPGUARD *)pgoal->pstep));
                } else
                    cmd.kind = 1;
            } else
                cmd.kind = 1;
        }
    }
    GoalBrain_SetCommand(pgoal, &cmd);
}
