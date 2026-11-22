// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
struct PO_SOURCE { char pad[0x184]; int unk184; };
struct MSGARGS { PO_SOURCE *psource; void *ptarget; };
struct GUARD { char pad[0xC]; void *field0C; };
extern "C" void HandlePoMessage(STEPGUARD *, int, MSGARGS *);
extern "C" void SetGuardDamageSource(GUARD *, PO_SOURCE *);
extern "C" void GoalStack_HandleMessage(void *, int, MSGARGS *);

void HandleStepguardMessage(STEPGUARD *pstepguard, int msg, MSGARGS *pargs)
{
    HandlePoMessage(pstepguard, msg, pargs);
    switch (msg) {
    case 4: {
        if (pargs->ptarget == pstepguard) {
            PO_SOURCE *psource = pargs->psource;
            if (psource->unk184 != 0)
                SetGuardDamageSource((GUARD *)pstepguard->field_0x49C, psource);
        }
        break;
    }
    case 5: {
        if (pargs->ptarget == pstepguard) {
            GUARD *pguard = (GUARD *)pstepguard->field_0x49C;
            if ((void *)pargs->psource == pguard->field0C)
                SetGuardDamageSource(pguard, 0);
        }
        break;
    }
    }
    GoalStack_HandleMessage((char *)pstepguard + 0x26C, msg, pargs);
}
