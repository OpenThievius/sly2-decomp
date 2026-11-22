// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
struct HITSOURCE { u8 unknown_0x0[0x184]; int field_0x184; };
struct MSGARGS { HITSOURCE *psource; void *ptarget; };
extern "C" void HandlePoMessage(STEPGUARD *, int, MSGARGS *);
extern "C" void SetGuardDamageSource(GUARDDAMAGE *, HITSOURCE *);
extern "C" void GoalStack_HandleMessage(GOALSTACK *, int, MSGARGS *);

void HandleStepguardMessage(STEPGUARD *pstepguard, int msg, MSGARGS *pargs)
{
    HandlePoMessage(pstepguard, msg, pargs);
    switch (msg) {
    case 4: {
        if (pargs->ptarget == pstepguard) {
            HITSOURCE *psource = pargs->psource;
            if (psource->field_0x184 != 0)
                SetGuardDamageSource(pstepguard->pdamage, psource);
        }
        break;
    }
    case 5: {
        if (pargs->ptarget == pstepguard) {
            GUARDDAMAGE *pdamage = pstepguard->pdamage;
            if ((void *)pargs->psource == pdamage->psource)
                SetGuardDamageSource(pdamage, 0);
        }
        break;
    }
    }
    GoalStack_HandleMessage(pstepguard->pgoalstack(), msg, pargs);
}
