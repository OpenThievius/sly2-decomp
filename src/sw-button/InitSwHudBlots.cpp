// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
extern SW B_003DD490;
extern "C" int D_002C3E70[];
extern "C" LO *PloFindSwObject_thunk(SW *psw, int grffso, int oid, LO *ploContext);
extern "C" void func_00213C68(LO *, float *);
extern "C" int CcluesFound();
extern "C" int func_001C7D00();
void InitSwHudBlots(SW *psw)
{
    float transform[8];
    memset(transform, 0, 0x20);
    transform[3] = 1.0f;
    transform[0] = 1.0f;
    for (int iblot = 0; iblot < 4; iblot++) {
        LO *pblot = PloFindSwObject_thunk(&B_003DD490, 0x405, D_002C3E70[iblot], 0);
        if (pblot) {
            func_00213C68(pblot, transform);
            psw->ahudblot[iblot].plo = pblot;
        }
    }
    psw->cclueFound = CcluesFound();
    psw->cclueMax = func_001C7D00();
}
