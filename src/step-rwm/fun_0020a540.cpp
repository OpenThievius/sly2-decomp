// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
extern "C" GOALBRAIN *GoalStack_PgoalFind(GOALSTACK *, int);
extern "C" void GoalBrain_SetCommand(GOALBRAIN *, GOALCMD *);

void func_0020A540(STEPGUARD *pguard, int variant)
{
    if (pguard->field_0x2E8 == variant)
        return;
    pguard->field_0x2E8 = variant;
    memset(pguard->scratch, 0, 0xC);
    GOALBRAIN *pgoal = GoalStack_PgoalFind(pguard->pgoalstack(), 0x9C);
    if (pgoal != 0) {
        int kind = pgoal->cmd.type;
        if (kind == 1) {
            GOALCMD cmd;
            memset(&cmd, 0, sizeof(cmd));
            cmd.type = -1;
            GoalBrain_SetCommand(pgoal, &cmd);
            memset(pguard->scratch, 0, 0xC);
            cmd.type = kind;
            GoalBrain_SetCommand(pgoal, &cmd);
        }
    }
}
