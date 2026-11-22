// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
// The guard's orientation, three quadword rows at STEP 0x1B0 (only this function reads it: a local view of the guard)
struct GUARDFACING {
    u8 unknown_0x0[0x1B0];
    QW facing[3];
};
struct M3 { QW row[3]; };
extern "C" QW g_2a2dc0;
extern "C" void func_001EEF70(GOAL *);
extern "C" GOAL *func_00205438(STEPGUARD *, int);
extern "C" QW *PmatLoWorld(void *);
extern "C" void BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3(M3 *, QW, QW);
void func_0017D1F0(GOAL *pgoal)
{
    M3 mat;
    func_001EEF70(pgoal);
    GOALANIM *panim = (GOALANIM *)func_00205438(GOAL_GUARD(pgoal), 0x9D);
    panim->sgs = 2;
    panim->Activate();
    GUARDFACING *pguard = (GUARDFACING *)pgoal->pstep;
    QW *path = PmatLoWorld(GOAL_GUARD(pgoal)->ptargetPath);
    BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3(&mat, path[0], g_2a2dc0);
    pguard->facing[0] = mat.row[0];
    pguard->facing[1] = mat.row[1];
    pguard->facing[2] = mat.row[2];
}
