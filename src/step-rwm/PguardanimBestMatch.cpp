// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" {
unsigned long GrfsgsFromSgs(int);
int CsgsMatchGrfsgs(unsigned long, unsigned long);
}
extern "C" GUARDANIM *PguardanimBestMatch(STEPGUARD *pguard, unsigned long grf)
{
    unsigned long lowest = 0;
    int csgsBest = 0;
    GUARDANIM *best = 0;
    for (int sgs = 0; sgs < 0x30;) {
        lowest = GrfsgsFromSgs(sgs);
        sgs++;
        if ((grf & lowest) != 0)
            break;
    }
    for (int index = 0; index < pguard->canim; index++) {
        GUARDANIM *anim = &pguard->aanim[index];
        int csgs = CsgsMatchGrfsgs(anim->grf, grf);
        if (csgs != 0 && (anim->grf & lowest) != 0 && csgsBest < csgs) {
            csgsBest = csgs;
            best = anim;
        }
    }
    return best;
}
