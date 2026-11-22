/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pathzone.h"

s32 ClsgClipEdgeToCg(void *pcg, QW posStart, QW posEnd, s32 mode, void *plsg, s32 clsgMax);

void ClsgClipEdgeToPathzone(struct PATHZONE *pzone, QW posStart, QW posEnd, s32 mode, void *plsg, s32 clsgMax) {
    ClsgClipEdgeToCg(&pzone->cg, posStart, posEnd, mode, plsg, clsgMax);
}
