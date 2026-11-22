/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crv.h"

void FindCrvcClosestPointFromU();                   /* extern */
void FindCrvlClosestPointFromU();                   /* extern */

void FindCrvClosestPointFromU(struct CRV *pcrv) {
    if (pcrv->crvk == 0) {
        FindCrvlClosestPointFromU();
        return;
    }
    FindCrvcClosestPointFromU();
}
