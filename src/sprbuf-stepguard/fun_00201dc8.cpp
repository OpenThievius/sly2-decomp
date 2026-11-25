// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "recon.h"
extern "C" char B_003DD490[];
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" void *PloFindSwObject_thunk(void *, int, int, void *);
extern "C" int CploFindSwObjectsByClass(void *, int, int, void *, int, RECON **);
extern "C" void HideReconLinks(BINOCRECON *);
void func_00201DC8(BINOCRECON *precon)
{
    if (FIsBasicDerivedFrom(*precon->pplo, 0x35)) {
        precon->pblotA = (BLOT *)PloFindSwObject_thunk(B_003DD490, 0x405, 0x362, 0);
        precon->pblotB = (BLOT *)PloFindSwObject_thunk(B_003DD490, 0x405, 0x365, 0);
    }
    precon->pobjWipe = PloFindSwObject_thunk(B_003DD490, 0x405, 0x602, 0);
    precon->ctarget = CploFindSwObjectsByClass(B_003DD490, 0x405, 0x2E, 0, 0x10, precon->aptarget);
    HideReconLinks(precon);
}
