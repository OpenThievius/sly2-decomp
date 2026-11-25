#include "sly2.h"
#include "goal.h"
#include "stepguard.h"
struct CMD { int op; u8 unknown_0x4[4]; float duration; };
struct BEH : GOAL { u8 unknown_0x30[8]; CMD *pcmd; float tStart; int fWaiting; u8 unknown_0x44[4]; float yaw; };
extern "C" {
int func_0017EE78(void *, CMD *);
int func_0017CE30(void *, CMD *);
int func_0017D188(void *, CMD *);
int GoalGoto_FArrived(void *, CMD *);
int FGoalAnimDone(void *, CMD *);
void func_00209818(void *, float);
void Goal_Pop(void *);
}
extern float g_2dded0;
// Retail loads pbeh->pcmd into $v0 for the switch, then copies it to $a1 (daddu $a1,$v0) before the jump table, and every
// case passes that copy as the second argument without reloading it. That copy is what gcse inserts when each case reads
// pbeh->pcmd again into its own pseudo: a scoped local per case (bound to the value the case passes on) reproduces it, while one
// local before the switch is loaded straight into $a1 (score 9) and passing pbeh->pcmd directly reloads it per call (score 27).
extern "C" int FGuardScriptWaiting(BEH *pbeh)
{
    if (pbeh->fWaiting == 0)
        return 0;
    switch (pbeh->pcmd->op) {
    case 6: {
        CMD *pcmd = pbeh->pcmd;
        switch (((STEPGUARD *)pbeh->pstep)->modePath) {
        case -1:
            if (func_0017EE78(pbeh->pgoalChild, pcmd))
                pbeh->fWaiting = 0;
            break;
        case 0:
            if (func_0017CE30(pbeh->pgoalChild, pcmd))
                pbeh->fWaiting = 0;
            break;
        case 1:
            if (func_0017D188(pbeh->pgoalChild, pcmd))
                pbeh->fWaiting = 0;
            break;
        }
        break;
    }
    case 7: {
        CMD *pcmd = pbeh->pcmd;
        if (GoalGoto_FArrived(pbeh->pgoalChild, pcmd)) {
            pbeh->fWaiting = 0;
            func_00209818(&((STEPGUARD *)pbeh->pstep)->heading, pbeh->yaw);
        }
        break;
    }
    case 5:
        if (pbeh->pcmd->duration < g_2dded0 - pbeh->tStart)
            pbeh->fWaiting = 0;
        break;
    case 13:
    case 14: {
        CMD *pcmd = pbeh->pcmd;
        if (FGoalAnimDone(pbeh->pgoalChild, pcmd))
            pbeh->fWaiting = 0;
        break;
    }
    }
    if (pbeh->fWaiting == 0)
        Goal_Pop(&pbeh->pgoalChild);
    return pbeh->fWaiting;
}
