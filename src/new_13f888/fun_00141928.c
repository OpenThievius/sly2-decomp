/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void GoalStack_Clear(struct GOALSTACK *pgoalstack);
void RemoveSoLoHierarchy(struct JTVIEW *pjt);
void RetractAsegaHandle(void **ppvHandle);

void func_00141928(struct JTVIEW *pjt) {
    RemoveSoLoHierarchy(pjt);
    RetractAsegaHandle(&pjt->pasegaHandle);
    RetractAsegaHandle(&pjt->pasegaHandle2);
    GoalStack_Clear(&pjt->goalstack);
}
