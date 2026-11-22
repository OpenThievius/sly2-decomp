// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "geom.h"
struct XP { GEOM *pgeom; u8 unknown_0x4[0x3C]; };
#include "bentley.h"
void AdjustJtZapNewXp(void *, XP *);
void func_0019E9C8(void *, XP *);
void AdjustStepNewXp(BENTLEY *, XP *, int);
void AdjustBentleyNewXp(BENTLEY *pbentley, XP *pxp, int ixpd)
{
    if ((((XP *)((char *)pxp + (ixpd << 6)))->pgeom->grf & (1UL << 48)) == 0) {
        switch (pbentley->state) {
        case 4:
            AdjustJtZapNewXp(pbentley->PvZap(), pxp);
            break;
        case 0xD:
            func_0019E9C8(pbentley->PvPipe(), pxp);
            break;
        default:
            AdjustStepNewXp(pbentley, pxp, ixpd);
        }
    }
}
