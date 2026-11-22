// SPDX-License-Identifier: GPL-3.0-or-later
#include "guardview.h"

void ClonePo(void *ppo, void *ppoSource);
void func_001EEC68(struct GOALSTACK *pgoalstack, struct STEPVIEW *pstep);

void CloneStep(struct STEPVIEW *pstep, struct STEPVIEW *pstepSource) {
    ClonePo(pstep, pstepSource);
    func_001EEC68(&pstep->goalstack, pstep);
}
