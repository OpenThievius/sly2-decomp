// SPDX-License-Identifier: GPL-3.0-or-later
#include "dancer.h"
extern "C" void *PaloFindDancerAnim(DANCER *, int);
void ResolveDancerMoves(DANCER *dancer)
{
    for (int imove = 0; imove < dancer->cmove; imove++) {
        // retail walks a bare pointer to each step's paseg; its oid is the word before
        void **ppaseg = &dancer->amove[imove].astep[0].paseg;
        for (int istep = 0; istep < 3; istep++) {
            int oid = ((int *)ppaseg)[-1];
            if (oid != -1)
                *ppaseg = PaloFindDancerAnim(dancer, oid);
            ppaseg += sizeof(DANCERSTEP) / sizeof(void *);
        }
    }
}
