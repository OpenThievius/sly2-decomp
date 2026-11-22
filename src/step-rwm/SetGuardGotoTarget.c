/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

struct GOAL *GoalStack_PgoalFind(struct GOALSTACK *, s32);

void SetGuardGotoTarget(struct STEPGUARDVIEW *pguard, struct LO *ptarget, QW posTarget) {
    struct LO *ptargetGoto;
    struct GOALBRAIN *pgoalBrain;
    struct GOALGOTOTARGET *pgoalGoto;

    pguard->ptargetGoto = ptarget;
    pguard->posGoto = posTarget;
    pgoalBrain = (struct GOALBRAIN *)GoalStack_PgoalFind(&pguard->goalstack, 0x9C);
    if (pgoalBrain != 0) {
        ptargetGoto = pguard->ptargetGoto;
        if ((ptargetGoto != 0) && (pgoalBrain->cmd.type == 0x10)) {
            pgoalGoto = (struct GOALGOTOTARGET *)pgoalBrain->pgoalChild;
            pgoalGoto->ptarget = ptargetGoto;
            pgoalGoto->offset = pguard->posGoto;
        }
    }
}
