// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
#include "xf.h"

/* an act that moves its transform to a goal: tArrive, posGoal and velGoal go to the XF */
struct ACTGOAL {
    ACT act;
    /* 0x1C */ f32 tArrive;
    /* 0x20 */ QW posGoal;
    /* 0x30 */ QW velGoal;
};

extern "C" {
void func_0022C818(ALO *palo, XF *pxf);        /* extern */

void func_0012E010(ACTGOAL *pact) {
    pact->act.pxf->tArrive = pact->tArrive;
    pact->act.pxf->posGoal = pact->posGoal;
    pact->act.pxf->velGoal = pact->velGoal;
    pact->act.pxf->sub = 2;
    func_0022C818(pact->act.palo, pact->act.pxf);
}

}
