// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "goal.h"
struct GOALCRV : GOAL {
    u8 unknown_0x30[0x78];
    int g0;
    int g1;
    u8 unknown_0xB0[0xC];
    int g2;
};
struct GOAL_17EB88 : GOAL {
    void *pcrv;
    u8 unknown_0x34[0x4];
    float s;
    u8 unknown_0x3C[0x4];
    QW pos;
    int g0;
    int g1;
    int g2;
};
extern "C" void func_001EEF70(void);
extern "C" QW PosLoWorld(void *);
extern "C" char B_003DD020;
extern "C" void FindCrvClosestPointFromS(void *, QW, float, void *, QW *, void *, void *, float *);
extern "C" void FindCrvClosestPointAll(void *, QW, void *, QW *, void *, void *, float *);
extern "C" GOALCRV *func_00205438(void *, int);
extern "C" void func_0017ECF0(GOAL_17EB88 *, int);
void func_0017EB88(GOAL_17EB88 *pgoal)
{
    func_001EEF70();
    QW posGuard;
    if (pgoal->s >= 0.0f) {
        posGuard = PosLoWorld(((void *)pgoal->pstep));
        FindCrvClosestPointFromS(pgoal->pcrv, posGuard, pgoal->s, &B_003DD020, &pgoal->pos, 0, 0, &pgoal->s);
    } else {
        posGuard = PosLoWorld(((void *)pgoal->pstep));
        FindCrvClosestPointAll(pgoal->pcrv, posGuard, &B_003DD020, &pgoal->pos, 0, 0, &pgoal->s);
    }
    GOALCRV *pobj = func_00205438(((void *)pgoal->pstep), 0xBA);
    pobj->g0 = pgoal->g0;
    pobj->g1 = pgoal->g1;
    pobj->g2 = pgoal->g2;
    func_0017ECF0(pgoal, 1);
    pobj->Activate();
}
