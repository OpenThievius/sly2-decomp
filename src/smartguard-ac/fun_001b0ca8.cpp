// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "xf.h"
#include "bis.h"
extern "C" {
void CSo_LoadFromBrx(SO *pso, CBinaryInputStream *pbis);
void ResolveSlotSoAsegs(SLOTSO *pso);
void SetXfKind(SO *pso, XF *pxf, int kind);

void func_001B0CA8(SLOTSO *pso, CBinaryInputStream *pbis) {
    CSo_LoadFromBrx(pso, pbis);
    SetXfKind(pso, pso->pxfLinear, 1);
    XF *pxfLinear = pso->pxfLinear;
    s32 *accel = pxfLinear->accel;
    accel[2] = 0;
    accel[1] = 0;
    pxfLinear->accel[0] = 0;
    pso->kindAngular = pso->pxfAngular->kind;
    ResolveSlotSoAsegs(pso);
}

}
