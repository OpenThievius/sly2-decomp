// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
struct WKROWNER { u8 unknown_0x0[0x14]; s32 field_0x14; };
struct WKRSOURCE { u8 unknown_0x0[0x200]; struct WKROWNER *powner; }; /* a class-0x4F object, the one that dealt the hit */
struct WKR { struct WKRSOURCE *psource; u8 unknown_0x4[0x8]; s32 grf; };
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" int FAbsorbSoWkr(STEPGUARD *, WKR *);
extern "C" void GoalStack_HandleMessage(GOALSTACK *, int, WKR *);
int FAbsorbGuardWkr(STEPGUARD *pguard, WKR *pwkr)
{
    if (pguard->FLethalHit()) goto post;
    if (pguard->FInvulnerable(pwkr->grf)) return 1;
    if (pwkr->psource && FIsBasicDerivedFrom(pwkr->psource, 0x4F) && pwkr->psource->powner->field_0x14 == (int)pguard->proot) return 1;
    if (!FAbsorbSoWkr(pguard, pwkr)) return 0;
post:
    GoalStack_HandleMessage(pguard->pgoalstack(), 0xC, pwkr);
    return 1;
}
