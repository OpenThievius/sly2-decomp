/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pathzone.h"

s32 FFindClosestPointInCg(struct CG *pcg, QW pos, QW *pposOut);

s32 FFindPathzoneClosestPoint(struct PATHZONE *pzone, QW pos, QW *pposOut) {
    return FFindClosestPointInCg(&pzone->cg, pos, pposOut);
}
