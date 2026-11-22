/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "act.h"

void SetActvalGoal(struct ACTVAL *pactval, QW posGoal, QW velGoal) {
    struct XF *pxf;

    pxf = pactval->act.pxf;
    pactval->posGoal = posGoal;
    pactval->velGoal = velGoal;
    if ((struct ACT *)pactval == pxf->pactFirst) {
        pxf->posGoal = posGoal;
        pactval->act.pxf->velGoal = velGoal;
    }
}
