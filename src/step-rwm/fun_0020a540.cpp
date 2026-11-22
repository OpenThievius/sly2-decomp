// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "goal.h"
struct GOAL_20A540 : GOAL {
    int kind;
};
struct GOALCMD { int kind; char pad[0x6C]; };
#include "stepguard.h"
extern "C" GOAL_20A540 *GoalStack_PgoalFind(void *, int);
extern "C" void GoalBrain_SetCommand(GOAL_20A540 *, GOALCMD *);

void func_0020A540(STEPGUARD *pguard, int variant)
{
    if (pguard->field_0x2E8 == variant)
        return;
    pguard->field_0x2E8 = variant;
    memset(pguard->scratch, 0, 0xC);
    GOAL_20A540 *pgoal = GoalStack_PgoalFind((char *)pguard + 0x26C, 0x9C);
    if (pgoal != 0) {
        int kind = pgoal->kind;
        if (kind == 1) {
            GOALCMD cmd;
            memset(&cmd, 0, sizeof(cmd));
            cmd.kind = -1;
            GoalBrain_SetCommand(pgoal, &cmd);
            memset(pguard->scratch, 0, 0xC);
            cmd.kind = kind;
            GoalBrain_SetCommand(pgoal, &cmd);
        }
    }
}
