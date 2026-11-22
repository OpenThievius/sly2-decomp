// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

void BindAnimref(struct ANIMREF *panimref, struct STEPGUARD *pguard);
void func_0020AFF0(struct AIMSTATE *paim, s32 id);

void func_0020B060(struct AIMSTATE *paim, s32 id) {
    func_0020AFF0(paim, id);
    BindAnimref(&paim->animref, paim->pguard);
}
