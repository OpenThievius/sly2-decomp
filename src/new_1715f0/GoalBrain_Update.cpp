// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "sw.h"
#include "po.h"
/* a new command starts from zero */
struct CMD : GOALCMD {
    CMD() { memset(this, 0, 0x70); }
};
struct HITFX;
/* class 52 (the player), the one field of it this reads: the object it is looking at (a guard, or the guard its object belongs to) */
struct JTVIEW {
    u8 unknown_0x0[0xE20];
    /* 0xE20 */ LO *field_0xE20;
};
extern "C" {
int FGoalAnimDone(GOALANIM *);
int FGoalNoticeDone(GOALNOTICE *);
int FGuardScriptDone(GOAL *);
int FIsBasicDerivedFrom(void *, int);
void GoalBrain_AbsorbDamage(GOALBRAIN *, int, int);
void GoalBrain_ChooseNextCommand(GOALBRAIN *);
int GoalBrain_FCmdEqual(GOALCMD *, GOALCMD *);
int GoalBrain_FGotoTargetInWorld(GOALBRAIN *);
void GoalBrain_SetCommand(GOALBRAIN *, GOALCMD *);
void HitFx_Remove(HITFX *);
HITFX *PhitfxChooseForGuard(STEPGUARD *, HITFX *);
QW PosLoWorld(LO *);
void SetSearchGoal(GOALSEARCH *, GOAL *);
HITFX *SpawnSwHitFx(SW *, int, QW, STEPGUARD *);
int func_00172550(GOALSEARCH *);
void *func_00174898(LO *);
int func_00177D20(GOALBRAIN *);
int func_0017A9C0(GOAL *);
int func_0017DE40(GOAL *);
int func_0017EAE8(GOAL *);
void func_001EEF98();
int func_001EF0A8(GOALBRAIN *);
int func_00208B38(STEPGUARD *, LO *);
float func_00208BB0(STEPGUARD *);
extern SW B_003DD490;
extern float g_2dded0;
void GoalBrain_Update(GOALBRAIN *goal) {
    func_001EEF98();
    while (func_001EF0A8(goal) == 0) {
        GOALCMD old(goal->cmd);
        switch ((u32)goal->cmd.type) {
        case 1:
        case 16:
        case 17:
        {
            CMD next;
            if (func_00177D20(goal) == 0) {
                STEPGUARD *pguard = GOAL_GUARD(goal);
                LO *ptarget = (LO *)pguard->Slot88();
                if (ptarget != 0) {
                    if (func_00208B38(GOAL_GUARD(goal), ptarget) != 0) {
                        next.type = 0x12;
                        next.args.arg = (s32)ptarget;
                        next.args.argf = func_00208BB0(GOAL_GUARD(goal));
                    } else {
                        next.args.arg = (s32)ptarget;
                        next.type = 3;
                    }
                } else {
                    HITFX *phitfx = PhitfxChooseForGuard(GOAL_GUARD(goal), 0);
                    if (phitfx != 0) {
                        next.args.arg = (s32)phitfx;
                        next.type = 2;
                    } else {
                        u32 type = goal->cmd.type;
                        if (type == 0x11 && g_2dded0 < goal->tRetry) {
                            next.type = type;
                        } else {
                            if (GoalBrain_FGotoTargetInWorld(goal) == 0)
                                next.type = 1;
                            else
                                next.type = 0x10;
                        }
                    }
                }
            } else {
                next.type = 0xC;
            }
            GoalBrain_SetCommand(goal, &next);
            break;
        }
        case 2:
        {
            if (func_00177D20(goal) != 0) {
                CMD next;
                next.type = 0xC;
                GoalBrain_SetCommand(goal, &next);
            } else {
                STEPGUARD *pguard = GOAL_GUARD(goal);
                LO *ptarget = (LO *)pguard->Slot88();
                if (ptarget != 0) {
                    CMD next;
                    if (func_00208B38(GOAL_GUARD(goal), ptarget) != 0) {
                        next.type = 0x12;
                        next.args.arg = (s32)ptarget;
                        next.args.argf = func_00208BB0(GOAL_GUARD(goal));
                    } else {
                        next.args.arg = (s32)ptarget;
                        next.type = 3;
                    }
                    GoalBrain_SetCommand(goal, &next);
                } else {
                    GOALSEARCH *search = (GOALSEARCH *)goal->pgoalChild;
                    HITFX *current = (HITFX *)search->pgoalSearch;
                    HITFX *chosen = PhitfxChooseForGuard(GOAL_GUARD(goal), current);
                    if (chosen != current) {
                        SetSearchGoal(search, (GOAL *)chosen);
                    } else if (func_00172550(search) != 0) {
                        CMD next;
                        next.type = 1;
                        GoalBrain_SetCommand(goal, &next);
                    }
                }
            }
            break;
        }
        case 3:
        {
            if (func_00177D20(goal) != 0) {
                CMD next;
                next.type = 0xC;
                GoalBrain_SetCommand(goal, &next);
            } else if (FGoalAnimDone((GOALANIM *)goal->pgoalChild) != 0) {
                CMD next;
                if (FIsBasicDerivedFrom(GOAL_GUARD(goal), 0x3B) != 0) {
                    next.type = 0xD;
                    next.args.arg = goal->cmd.args.arg;
                } else {
                    next.type = 4;
                    next.args.arg = goal->cmd.args.arg;
                }
                GoalBrain_SetCommand(goal, &next);
            }
            break;
        }
        case 5:
            if (FGuardScriptDone(goal->pgoalChild) != 0) GoalBrain_ChooseNextCommand(goal);
            break;
        case 4:
        {
            GOALNOTICE *notice = (GOALNOTICE *)goal->pgoalChild;
            if (func_00177D20(goal) != 0) {
                CMD next;
                next.type = 0xC;
                GoalBrain_SetCommand(goal, &next);
            } else if (FGoalNoticeDone(notice) == 0) {
                STEPGUARD *pguard = GOAL_GUARD(goal);
                LO *ptarget = (LO *)pguard->Slot88();
                if (ptarget != GOAL_GUARD(goal)->pbasicAlert) {
                    CMD next;
                    if (ptarget != 0) {
                        if (func_00208B38(GOAL_GUARD(goal), ptarget) != 0) {
                            next.type = 0x12;
                            next.args.arg = (s32)ptarget;
                            next.args.argf = func_00208BB0(GOAL_GUARD(goal));
                        } else {
                            next.args.arg = (s32)ptarget;
                            next.type = 3;
                        }
                    } else {
                        next.type = 1;
                        LO *pother = notice->ptarget;
                        if (pother != 0) {
                            if (FIsBasicDerivedFrom(pother, 0x34) != 0) {
                                if (((PO *)pother)->NAlertLevel() == 2) {
                                    void *pvictim = func_00174898(((JTVIEW *)pother)->field_0xE20);
                                    if (pvictim != 0) {
                                        if (pvictim != GOAL_GUARD(goal)) {
                                            next.args.arg = (s32)pvictim;
                                            next.type = 0x11;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    GoalBrain_SetCommand(goal, &next);
                }
            } else {
                CMD next;
                next.type = 1;
                GoalBrain_SetCommand(goal, &next);
            }
            break;
        }
        case 0:
        {
            CMD next;
            next.type = 1;
            GoalBrain_SetCommand(goal, &next);
            break;
        }
        case 12:
        {
            if (func_00177D20(goal) == 0) {
                CMD next;
                next.type = 1;
                GoalBrain_SetCommand(goal, &next);
            }
            break;
        }
        case 8:
        {
            if (FGoalAnimDone((GOALANIM *)goal->pgoalChild) != 0) {
                HITFX *phitfx = SpawnSwHitFx(&B_003DD490, 0, PosLoWorld(goal->pstep), GOAL_GUARD(goal));
                CMD next;
                next.type = 2;
                next.args.arg = (s32)phitfx;
                GoalBrain_SetCommand(goal, &next);
                HitFx_Remove(phitfx);
            }
            break;
        }
        case 7:
        {
            GOALGRAB *pb1 = (GOALGRAB *)goal->pgoalChild;
            if (FGoalAnimDone(pb1) != 0) {
                int phase = pb1->phase;
                if (phase != -1) {
                    if (phase == 3) GoalBrain_ChooseNextCommand(goal);
                } else {
                    GoalBrain_AbsorbDamage(goal, -0x32, (s32)pb1->psoHeld);
                    if (goal->cmd.type == 7) GoalBrain_ChooseNextCommand(goal);
                }
            }
            break;
        }
        case 6:
            if (func_0017A9C0(goal->pgoalChild) != 0) GoalBrain_ChooseNextCommand(goal);
            break;
        case 9:
            if (FGoalAnimDone((GOALANIM *)goal->pgoalChild) != 0) GoalBrain_ChooseNextCommand(goal);
            break;
        case 10:
            if (FGoalAnimDone((GOALANIM *)goal->pgoalChild) != 0) GoalBrain_ChooseNextCommand(goal);
            break;
        case 19:
            if (func_0017EAE8(goal->pgoalChild) != 0) GoalBrain_ChooseNextCommand(goal);
            break;
        case 18:
            if (func_0017DE40(goal->pgoalChild) != 0) GoalBrain_ChooseNextCommand(goal);
            break;
        default:
            break;
        }
        if (GoalBrain_FCmdEqual(&goal->cmd, &old) != 0) break;
    }
}
}
