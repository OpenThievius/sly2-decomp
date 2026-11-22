// SPDX-License-Identifier: GPL-3.0-or-later
#include "goalpatrol.h"
#include "sw.h"
extern "C" {
int FGoalAnimDone(GOAL *);
int FGoalReactDone(GOAL *);
int GoalFollowCrv_FAtEnd(GOAL *);
PO *PpoSwFocusBase(SW *);
NOTICE *PsenseFindNotice(STEPGUARD *, LO *, int);
int func_0014A478(GOALPATROL *);
int func_0014A4D0(GOALPATROL *);
int func_0014AA30(GOALPATROL *);
void func_0014AD70(GOALPATROL *);
void func_0014AE38(GOALPATROL *, int);
void func_001EEF98(GOALPATROL *);
int func_001EF0A8(GOALPATROL *);
int func_00209098(STEPGUARD *);
extern SW B_003DD490;
}
void func_0014A2A0(GOALPATROL *pgoal)
{
    int done;
    func_001EEF98(pgoal);
    func_0014A4D0(pgoal);
    while (func_001EF0A8(pgoal) == 0) {
        unsigned int state = pgoal->state;
        switch (state) {
        case 0:
            if (func_00209098(GOAL_GUARD(pgoal)) != 0)
                goto busy;
            if (func_0014A478(pgoal) != 0)
                goto reacted;
            {
                int inodeTarget = func_0014AA30(pgoal);
                pgoal->inodeTarget = inodeTarget;
                if (inodeTarget == pgoal->inodeCur) {
                    NOTICE *pnotice = PsenseFindNotice(GOAL_GUARD(pgoal), PpoSwFocusBase(&B_003DD490), 0);
                    pgoal->pnotice = pnotice;
                    if (pnotice != 0)
                        func_0014AE38(pgoal, 3);
                } else {
                    func_0014AD70(pgoal);
                }
            }
            break;
        case 1:
            if (func_00209098(GOAL_GUARD(pgoal)) != 0)
                goto busy;
            if (func_0014A478(pgoal) != 0) {
            reacted:
                func_0014AE38(pgoal, 2);
                break;
            }
            if (GoalFollowCrv_FAtEnd(pgoal->pgoalChild) != 0)
                goto idle;
            PsenseFindNotice(GOAL_GUARD(pgoal), PpoSwFocusBase(&B_003DD490), 0);
            break;
        case 2:
            if (func_00209098(GOAL_GUARD(pgoal)) != 0)
                goto busy;
            done = FGoalAnimDone(pgoal->pgoalChild);
            goto check;
        case 3:
            if (func_00209098(GOAL_GUARD(pgoal)) != 0) {
            busy:
                func_0014AE38(pgoal, 4);
                break;
            }
            done = FGoalReactDone(pgoal->pgoalChild);
        check:
            if (done != 0) {
            idle:
                func_0014AE38(pgoal, 0);
            }
            break;
        case 4:
            if (func_00209098(GOAL_GUARD(pgoal)) == 0)
                func_0014AE38(pgoal, 0);
            break;
        }
        if (state == pgoal->state)
            break;
    }
}
