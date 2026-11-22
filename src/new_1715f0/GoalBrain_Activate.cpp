// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" {

void GoalBrain_SetCommand(GOALBRAIN *goal, GOALCMD *pcmd);
void func_001EEF70();

void GoalBrain_Activate(GOALBRAIN *goal) {
    GOALCMD cmd;

    func_001EEF70();
    memset(&cmd, 0, 0x70);
    cmd.type = 0;
    GoalBrain_SetCommand(goal, &cmd);
}

}
