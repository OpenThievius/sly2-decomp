// SPDX-License-Identifier: GPL-3.0-or-later
#include "goalpost.h"
extern "C" {
QW PosLoWorld(LO *);
int func_00227C90(LO *, QW);

/* PloPostSide */
LO *func_00155A68(GOALPOSTWATCH *pgoal)
{
    POSTPAIR *ppost;

    ppost = pgoal->ppost;
    if (func_00227C90(ppost->pvolumeA, PosLoWorld(pgoal->ploTarget)) != 0
        || (ppost = pgoal->ppost, func_00227C90(ppost->pvolumeB, PosLoWorld(pgoal->ploTarget)) == 0)) {
        return pgoal->ppost->ploA;
    }
    return pgoal->ppost->ploB;
}
}
