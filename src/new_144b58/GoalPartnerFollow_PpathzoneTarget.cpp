// SPDX-License-Identifier: GPL-3.0-or-later
#include "goals.h"
#include "so.h"
#include "phys.h"

struct PATHZONE;
struct LINK { /* the region link of a PHYS: only the zone is read here */
    u8 unknown_0x0[0x10];
    /* 0x10 */ struct PATHZONE *pzone;
};

extern "C" {
int FIsBasicDerivedFrom(LO *plo, int index);
QW PosLoWorld(LO *plo);
PATHZONE *PpathzoneFindPos(QW pos, int flag);

PATHZONE *GoalPartnerFollow_PpathzoneTarget(GOALPARTNERFOLLOW *pgoal)
{
    if (FIsBasicDerivedFrom(pgoal->ploLeader, 0x30) != 0) {
        PHYS *pphys = ((SO *)pgoal->ploLeader)->pphys;
        LINK *plink = 0;
        if (pphys != 0) {
            plink = pphys->plink;
        }
        if (plink != 0) {
            return plink->pzone;
        }
        return 0;
    }
    return PpathzoneFindPos(PosLoWorld(pgoal->ploLeader), 1);
}
}
