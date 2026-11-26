// SPDX-License-Identifier: GPL-3.0-or-later
#include "goals.h"
#include "sly2.h"
extern "C" void func_001EEF70(void);
extern "C" QW PosLoWorld(void *);
extern "C" char B_003DD020;
extern "C" void FindCrvClosestPointFromS(void *, QW, float, void *, QW *, void *, void *, float *);
extern "C" void FindCrvClosestPointAll(void *, QW, void *, QW *, void *, void *, float *);
extern "C" GOALGOTO *func_00205438(void *, int);
extern "C" void func_0017ECF0(GOALFOLLOWCURVE *, int);
void func_0017EB88(GOALFOLLOWCURVE *pgoal)
{
    func_001EEF70();
    QW posGuard;
    if (pgoal->s >= 0.0f) {
        posGuard = PosLoWorld(((void *)pgoal->pstep));
        FindCrvClosestPointFromS((void *)pgoal->pcrv, posGuard, pgoal->s, &B_003DD020, &pgoal->pos, 0, 0, &pgoal->s);
    } else {
        posGuard = PosLoWorld(((void *)pgoal->pstep));
        FindCrvClosestPointAll((void *)pgoal->pcrv, posGuard, &B_003DD020, &pgoal->pos, 0, 0, &pgoal->s);
    }
    GOALGOTO *pobj = func_00205438(((void *)pgoal->pstep), 0xBA);
    pobj->ptarget = (LO *)pgoal->poidOther;
    pobj->field_0xAC = pgoal->field_0x54;
    pobj->fStraight = pgoal->field_0x58;
    func_0017ECF0(pgoal, 1);
    pobj->Activate();
}
