// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "stepguard.h"
#include "goals.h"
extern "C" void UpdateStep(STEPGUARD *);
extern "C" void UpdateGuardModeTimeout(STEPGUARD *);
extern "C" void UpdateGuardSensor(STEPGUARD *);
extern "C" int FDoneAnimref(void *);
extern "C" void func_0020AB68(STEPGUARD *, int, int, QW);
extern "C" void func_0020ACC0(STEPGUARD *);
extern "C" void func_001F1CF8(STEPGUARD *);
extern "C" void UpdateFallCheck(FALLCHECK *);
extern "C" void UpdateGuardDamage(GUARDDAMAGE *);
extern "C" void GoalStack_Update(GOALSTACK *);
extern "C" void func_002097E0(GUARDHEADING *);
extern "C" int FAsegaGone(ASEGA *);
extern "C" void ReleaseAsegaHandle(ASEGA **);
extern "C" QW g_2a2dd0;

void UpdateGuard(STEPGUARD *pguard)
{
    UpdateStep(pguard);
    if (((pguard->grfo >> 60) & 1) == 0 || pguard->mode == 0xE)
        return;
    UpdateGuardModeTimeout(pguard);
    UpdateGuardSensor(pguard);
    if (pguard->paimstate != 0 && FDoneAnimref(pguard->paimstate->panimref))
        func_0020AB68(pguard, 0, 0, g_2a2dd0);
    if (pguard->pact != 0)
        func_0020ACC0(pguard);
    if (pguard->fActionDone != 0)
        func_001F1CF8(pguard);
    UpdateFallCheck(pguard->pfallcheck);
    UpdateGuardDamage(pguard->pdamage);
    GoalStack_Update(pguard->pgoalstack());
    func_002097E0(&pguard->heading);
    if (pguard->pasega != 0 && FAsegaGone(pguard->pasega))
        ReleaseAsegaHandle(&pguard->pasega);
    if (pguard->field_0x4A4 != 0 && pguard->psoSurface != 0)
        pguard->posCopy = *pguard->ppos;
}
