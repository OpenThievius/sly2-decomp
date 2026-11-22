// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "so.h"
#include "oxa.h"
extern "C" int FIgnoreSoIntersection(STEPGUARD *, SO *);
extern "C" int FIsGuardInSgs(STEPGUARD *, int);
extern "C" GOAL *GoalStack_PgoalFind(GOALSTACK *, int);
extern "C" int IMax(int, int);
int func_00206380(STEPGUARD *pguard, SO *pso)
{
    int result = FIgnoreSoIntersection(pguard, pso);
    int state;
    int fKeep;
    GOALGRAB *pgoal;
    if (FIsGuardInSgs(pguard, 7)) {
        fKeep = pso->FIsLocked();
        goto check;
    }
    if (FIsGuardInSgs(pguard, 0x17)) {
        pgoal = (GOALGRAB *)GoalStack_PgoalFind(pguard->pgoalstack(), 0xB1);
        if (pso->poxa == pgoal->psoHeld->poxa) {
            state = pgoal->phase;
            if (state != 0) {
                if (state >= 0) {
                    if (state < 6) {
                        fKeep = state < 4;
check:
                        if (fKeep) return result;
                    } else return result;
                } else return result;
            }
            result = IMax(result, 1);
        }
    }
    return result;
}
