// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "so.h"
#include "murray.h"
struct XF;
struct CARRY { char pad[0x180]; SO *so; };
extern "C" void func_0012E460(void *);
extern "C" void SetXfKind(SO *, XF *, int);
extern "C" void SetSoNoXpsAll(SO *, int);
extern "C" void func_001A58D0(SO *, int, int);
extern "C" void RecalcSwOxfFilterForObject(void *, MURRAY *);
extern "C" char B_003DD490[];
extern "C" float g_2dded0;
extern "C" void DetachMurrayObject(MURRAY *pmurray)
{
    func_0012E460(&pmurray->field_0x13F4);
    func_0012E460(&pmurray->field_0x13F8);
    func_0012E460(&pmurray->field_0x13FC);
    func_0012E460(&pmurray->field_0x1400);
    func_0012E460(&pmurray->field_0x1600);
    func_0012E460(&pmurray->field_0x1604);
    func_0012E460(&pmurray->field_0x1608);
    func_0012E460(&pmurray->field_0x160C);
    func_0012E460(&pmurray->field_0x1618);
    func_0012E460(&pmurray->field_0x161C);
    func_0012E460(&pmurray->field_0x1620);
    func_0012E460(&pmurray->field_0x1624);
    LO *plo = pmurray->ploCarried;
    if (plo == 0)
        return;
    plo->HandleSpliceEvent(6, 0, 0, 0, 0);
    SO *pso = ((CARRY *)pmurray->ploCarried)->so;
    SetXfKind(pso, pso->pxfLinear, pmurray->field_0x1404);
    SetXfKind(pso, pso->pxfAngular, pmurray->field_0x1408);
    SetSoNoXpsAll(pso, 0);
    func_001A58D0(pso, 0, 0xF);
    *(SO **)((char *)pmurray + 0x1430) = pso; /* a member store is scheduled after the float load: retail keeps it before */
    pmurray->field_0x1434 = g_2dded0;
    RecalcSwOxfFilterForObject(B_003DD490, pmurray);
}
