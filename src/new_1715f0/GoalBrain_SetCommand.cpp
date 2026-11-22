// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
/* a guard of class 0x3C (60, a STEPGUARD subclass): the word past STEPGUARD it holds (func_00177D70 reads it too) */
struct GUARD3C : STEPGUARD {
    u8 unknown_0x1010[0x7C];
    /* 0x108C */ LO *field_0x108C;
};
extern "C" {
float GRandInRange(float, float);
int GoalBrain_FCmdEqual(GOALCMD *, GOALCMD *);
void Goal_Pop(GOAL **ppgoal);
void SetGuardScript(GOAL *, int, int, int);
void SetSearchGoal(GOALSEARCH *, GOAL *);
GOAL *func_00205438(STEPGUARD *, int);
void func_00208540(STEPGUARD *, LO *);
extern float D_002BE618[2];
extern float g_2dded0;
void GoalBrain_SetCommand(GOALBRAIN *goal, GOALCMD *pcmd) {
    if (GoalBrain_FCmdEqual(pcmd, &goal->cmd) == 0) {
        Goal_Pop(&goal->pgoalChild);
        goal->cmd = *pcmd;
        goal->tCommand = g_2dded0;
        int notify = 0;
        switch (pcmd->type) {
        case 5: {
            notify = 1;
            GOAL *script = func_00205438(GOAL_GUARD(goal), 0xA9);
            SetGuardScript(script, pcmd->args.arg, 1, 0);
            script->Activate();
            break;
        }
        case 1: {
            notify = 1;
            GOAL *idle = func_00205438(GOAL_GUARD(goal), 0xAA);
            idle->Activate();
            break;
        }
        case 3: {
            GOALANIM *anim = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0x9D);
            anim->sgs = 0xB;
            anim->ptarget = (LO *)pcmd->args.arg;
            anim->Activate();
            break;
        }
        case 4: {
            GOALNOTICE *notice = (GOALNOTICE *)func_00205438(GOAL_GUARD(goal), 0xA5);
            notice->ptarget = (LO *)pcmd->args.arg;
            notice->Activate();
            break;
        }
        case 2: {
            notify = 1;
            GOALSEARCH *search = (GOALSEARCH *)func_00205438(GOAL_GUARD(goal), 0xAB);
            SetSearchGoal(search, (GOAL *)pcmd->args.arg);
            search->Activate();
            break;
        }
        case 9: {
            GOALHIT *withArgs = (GOALHIT *)func_00205438(GOAL_GUARD(goal), 0xA1);
            withArgs->args = pcmd->args;
            withArgs->Activate();
            break;
        }
        case 10: {
            GOALHIT *withArgs = (GOALHIT *)func_00205438(GOAL_GUARD(goal), 0xA2);
            withArgs->args = pcmd->args;
            withArgs->Activate();
            break;
        }
        case 11: {
            GOALHIT *withArgs = (GOALHIT *)func_00205438(GOAL_GUARD(goal), 0xA3);
            withArgs->args = pcmd->args;
            withArgs->Activate();
            notify = 1;
            break;
        }
        case 8: {
            GOAL *react = func_00205438(GOAL_GUARD(goal), 0xAF);
            react->Activate();
            break;
        }
        case 6: {
            GOALB0 *hit = (GOALB0 *)func_00205438(GOAL_GUARD(goal), 0xB0);
            hit->phitter = (void *)goal->cmd.args.arg;
            hit->Activate();
            break;
        }
        case 7: {
            GOALGRAB *b1 = (GOALGRAB *)func_00205438(GOAL_GUARD(goal), 0xB1);
            b1->psoHeld = (SO *)pcmd->args.arg;
            b1->Activate();
            break;
        }
        case 12: {
            GOAL *stunned = func_00205438(GOAL_GUARD(goal), 0xB2);
            stunned->Activate();
            break;
        }
        case 13: {
            GOALANIM *anim = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0xB4);
            anim->ptarget = (LO *)pcmd->args.arg;
            anim->Activate();
            break;
        }
        case 14: {
            GOALANIM *anim = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0xB6);
            anim->ptarget = (LO *)pcmd->args.arg;
            anim->Activate();
            break;
        }
        case 15: {
            GOALANIM *anim = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0xAE);
            anim->ptarget = ((GUARD3C *)goal->pstep)->field_0x108C;
            anim->Activate();
            break;
        }
        case 16: {
            notify = 1;
            GOALGOTOTARGET *b7 = (GOALGOTOTARGET *)func_00205438(GOAL_GUARD(goal), 0xB7);
            b7->ptarget = GOAL_GUARD(goal)->ptargetGoto;
            b7->offset = GOAL_GUARD(goal)->posGoto;
            b7->Activate();
            break;
        }
        case 17: {
            GOALANIM *anim = (GOALANIM *)func_00205438(GOAL_GUARD(goal), 0x9E);
            anim->sgs = 0x1A;
            anim->ptarget = (LO *)pcmd->args.arg;
            anim->Activate();
            float now = g_2dded0;
            goal->tRetry = now + GRandInRange(D_002BE618[0], D_002BE618[1]);
            break;
        }
        case 18: {
            GOALFLEE *bd = (GOALFLEE *)func_00205438(GOAL_GUARD(goal), 0xBD);
            bd->ptarget = (LO *)pcmd->args.arg;
            bd->field_0x40 = pcmd->args.argf;
            bd->Activate();
            break;
        }
        case 19: {
            GOALSNAPTOPOINT *bf = (GOALSNAPTOPOINT *)func_00205438(GOAL_GUARD(goal), 0xBF);
            bf->target.pos = GOAL_GUARD(goal)->posCopy;
            bf->Activate();
            break;
        }
        }
        if (notify != 0) func_00208540(GOAL_GUARD(goal), 0);
    }
}
}
