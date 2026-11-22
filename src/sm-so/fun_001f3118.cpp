// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
extern "C" void RemoveAloFromRenderTree(SO *);
extern "C" void AddAloToRenderTree(SO *);
extern "C" void ReinsertSwRoot(void *, int);
extern char B_003DD490;
extern "C" void func_001F3118(SO *pso, float value)
{
    VECTOR vector;
    pso->field_0x38 = value;
    if (pso->field_0x140 != -1) {
        RemoveAloFromRenderTree(pso);
        AddAloToRenderTree(pso);
    }
    if (pso->psoParent == 0 && ((unsigned)(pso->grfo >> 60) & 1)) {
        ReinsertSwRoot(&B_003DD490, pso->proot);
    }
    LO *plo = (LO *)pso->dlChild.head;
    while (plo) {
        if (value < plo->field_0x38) {
            plo->Slot42(value);
        }
        plo = plo->ploNext;
    }
}
