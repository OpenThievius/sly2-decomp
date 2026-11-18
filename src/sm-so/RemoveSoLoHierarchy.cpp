// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
#include "sw.h"
struct UL { unsigned long v; } __attribute__((packed));
extern "C" {
void RemoveLoHierarchy(SO *);
void RemoveSoGeomsFromOxa(SO *);
void CancelSwCallbacks(SW *, unsigned, SO *, unsigned long, int);
void func_001F37C8(SO *, int);
extern SW B_003DD490;
extern const UL RO_002A8270;
}

extern "C" void RemoveSoLoHierarchy(SO *pso)
{
    RemoveLoHierarchy(pso);
    RemoveSoGeomsFromOxa(pso);
    pso->duFade = 0.0f;
    pso->uFade = 1.0f;
    PHYS *pphys = pso->pphys;
    int hasXr = 0;
    if (pphys != 0) {
        hasXr = *(int *)((char *)pphys + 0xDC);
    }
    if (hasXr != 0) {
        CancelSwCallbacks(&B_003DD490, 3, pso, RO_002A8270.v, 0);
        func_001F37C8(pso, 0);
    }
    DLI dli;
    PushDli(&dli, &pso->dlChild);
    LO *plo;
    for (plo = (LO *)PvStep(&dli); plo != 0 && (plo->grfo & (0x8000UL << 41)) == 0; plo = (LO *)PvStep(&dli))
        plo->RemoveHierarchy();
    PopDli(&dli);
}
