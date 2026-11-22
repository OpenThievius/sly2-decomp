// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"
#include "so.h"

void func_001F3078(SO *pso, unsigned mask)
{
    struct G { int a; ~G() {} };
    G g;
    unsigned f = pso->grfSw;
    if ((f ^ 1) & 1)
        *(unsigned *)pso->pgrfentry &= ~mask;
    else
        pso->grfSw = f & ~mask;
    for (LO *plo = (LO *)pso->dlChild.head; plo != pso->ploChildEnd; plo = plo->ploNext)
        plo->ClearGrfField(mask);
}
