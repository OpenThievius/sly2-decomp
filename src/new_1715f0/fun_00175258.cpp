// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {

void GoalAnim_Update(GOALANIM *goal);
QW PosLoWorld(LO *plo);
void SetJumperTarget(JUMPER *pjumper, QW vec);

void func_00175258(GOALTRACK *goal) {
    ANIMREF *panimref;
    QW vec;

    GoalAnim_Update(goal);
    if ((goal->panimref == 0) || (goal->panimref->pinst == 0)) {
        goal->fTrackTarget = 0;
    }
    if (goal->fTrackTarget != 0) {
        panimref = goal->panimref;
        vec = PosLoWorld(goal->ptarget);
        SetJumperTarget((JUMPER *)panimref->pinst, vec);
    }
}
}
