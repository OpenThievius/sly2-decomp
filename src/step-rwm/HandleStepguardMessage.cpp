// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
struct MSGARGS { SRC_DAMAGE *psource; void *ptarget; };
extern "C" void HandlePoMessage(STEPGUARD *, int, MSGARGS *);
extern "C" void SetGuardDamageSource(GUARDDAMAGE *, SRC_DAMAGE *);
extern "C" void GoalStack_HandleMessage(GOALSTACK *, int, MSGARGS *);

void HandleStepguardMessage(STEPGUARD *pstepguard, int msg, MSGARGS *pargs)
{
    HandlePoMessage(pstepguard, msg, pargs);
    switch (msg) {
    case 4: {
        if (pargs->ptarget == pstepguard) {
            SRC_DAMAGE *psource = pargs->psource;
            if (psource->ndamage != 0)
                SetGuardDamageSource(pstepguard->pdamage, psource);
        }
        break;
    }
    case 5: {
        if (pargs->ptarget == pstepguard) {
            GUARDDAMAGE *pdamage = pstepguard->pdamage;
            if ((void *)pargs->psource == pdamage->psrc)
                SetGuardDamageSource(pdamage, 0);
        }
        break;
    }
    }
    GoalStack_HandleMessage(pstepguard->pgoalstack(), msg, pargs);
}
