/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void GoalStack_Clear(struct GOALSTACK *);
void RemoveSoLoHierarchy(struct STEPGUARDVIEW *);
void RetractAsegaHandle(struct ASEGA **);
void func_00208540(struct STEPGUARDVIEW *, struct BASIC *);

void func_002064D8(struct STEPGUARDVIEW *pguard) {
    RemoveSoLoHierarchy(pguard);
    func_00208540(pguard, 0);
    GoalStack_Clear(&pguard->goalstack);
    RetractAsegaHandle(&pguard->pasega);
}
