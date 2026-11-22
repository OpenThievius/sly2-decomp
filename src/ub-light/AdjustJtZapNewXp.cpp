// SPDX-License-Identifier: GPL-3.0-or-later
#include "jtzap.h"
extern "C" {
extern float RO_002BFB20;
extern float RO_002BFB24;

void AdjustJtZapNewXp(JTZAP *pzap, ZAPXP *pxp) {
    float first;
    float second;

    switch (pzap->state) {
    case 0:
    case 6:
    case 7:
        break;
    case 4:
    case 12:
        pxp->field_0x94 = RO_002BFB20;
        pxp->field_0x98 = 0;
        break;
    default:
        first = RO_002BFB20;
        second = RO_002BFB24;
        pxp->field_0x94 = first;
        pxp->field_0x98 = second;
        break;
    }
}
}
