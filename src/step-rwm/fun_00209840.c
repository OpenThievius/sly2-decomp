/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void func_00209840(struct GUARDHEADING *pheading, struct MATRIX3Q *pmat) {
    struct STEPVIEW *pstep;

    if (pheading->fHold == 0) {
        pstep = (struct STEPVIEW *)pheading->pstep;
        pstep->matHeading.row[0] = pmat->row[0];
        pstep->matHeading.row[1] = pmat->row[1];
        pstep->matHeading.row[2] = pmat->row[2];
    }
}
