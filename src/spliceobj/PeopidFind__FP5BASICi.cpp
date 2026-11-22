// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"
#include "splopt.h"
extern ARYSPLOPT RO_00279AD0[];
struct CLASSINFO { int pad; int cid; };
void *PeopidFind__FP5BASICi(BASIC *pbasic, int optid)
{
    CLASSINFO *pclassinfo = pbasic->Slot6();
    const ARYSPLOPT *parysplopt = &RO_00279AD0[pclassinfo->cid];
    int low = 0;
    int high = parysplopt->csplopt - 1;
    SPLOPT *asplopt = parysplopt->asplopt;
    if (high >= 0) {
        do {
            int mid = (low + high) >> 1;
            const SPLOPT *psplopt = (const SPLOPT *)((char *)(mid << 3) + (sptr)asplopt);
            if (psplopt->optid == optid)
                return psplopt->peopid;
            if (optid < psplopt->optid)
                high = mid - 1;
            else
                low = mid + 1;
        } while (low <= high);
    }
    return 0;
}
