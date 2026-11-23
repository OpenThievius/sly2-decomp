/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pathzone.h"

s32 FClipEdgeToCg(struct CG *pcg, QW posFrom, QW posTo, s32 flags);

s32 FClipEdgeToPathzone(struct PATHZONE *pzone, QW posFrom, QW posTo, s32 flags) {
    return FClipEdgeToCg(&pzone->cg, posFrom, posTo, flags);
}
