/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "acrc.h"
#include "sly2.h"


void CopyAb__FPvT0Ui(void *dest, void *src, unsigned int size); /* extern */

void EvaluateAcrc(struct ACRC *pacrc, void *pvecPos, struct VECTOR *pvecVel) {
    if (pvecPos != 0) {
        CopyAb__FPvT0Ui(pvecPos, pacrc->pos, 0xC);
    }
    if (pvecVel != 0) {
        pvecVel->z = 0.0f;
        pvecVel->y = 0.0f;
        pvecVel->x = 0.0f;
    }
}
