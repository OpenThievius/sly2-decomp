// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
struct SW;
extern SW B_003DD490;
extern "C" int PloFindSwObject_thunk(SW *, int, int, STEPGUARD *);

void ResolveGuardAimObjects(STEPGUARD *pguard)
{
    pguard->cfound = 0;
    for (int index = 0; index < pguard->caoid; index++) {
        int pobject = PloFindSwObject_thunk(&B_003DD490, 4, pguard->aoid[index], pguard);
        if (pobject != 0) {
            int n = pguard->cfound;
            pguard->afound[n] = pobject;
            pguard->cfound = n + 1;
        }
    }
}
