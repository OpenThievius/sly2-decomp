// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
#include "wkr.h"
#include "bomb.h"
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" int FAbsorbSoWkr(STEPGUARD *, WKR *);
extern "C" void GoalStack_HandleMessage(GOALSTACK *, int, WKR *);
int FAbsorbGuardWkr(STEPGUARD *pguard, WKR *pwkr)
{
    if (pguard->FLethalHit()) goto post;
    if (pguard->FInvulnerable(pwkr->grftak)) return 1;
    if (pwkr->psoSource && FIsBasicDerivedFrom(pwkr->psoSource, 0x4F) && ((BOMB *)pwkr->psoSource)->pbombOwner->proot == (int)pguard->proot) return 1;
    if (!FAbsorbSoWkr(pguard, pwkr)) return 0;
post:
    GoalStack_HandleMessage(pguard->pgoalstack(), 0xC, pwkr);
    return 1;
}
