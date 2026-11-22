// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
extern "C" {
/* handle is the address of an ACT pointer: the animation act is an ASEGA (HandleSlotSoMessage compares message acts with it) */
void ApplyAsegToHandle(struct ASEG *paseg, int paloRoot, int grfapl, struct ACT **handle, float tLocal, float svtLocal);
void RemoveSoLoHierarchy(SO *pso);

void func_001B0C68(SLOTSO *pso) {
    RemoveSoLoHierarchy(pso);
    ApplyAsegToHandle(0, 0, 0, &pso->pactAnim, 0, 0);
}

}
