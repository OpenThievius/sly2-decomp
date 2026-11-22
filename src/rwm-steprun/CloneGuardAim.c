// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

void CLo_Clone(struct LO *plo, struct LO *ploBase);
void CloneAnimref(struct ANIMREF *panimref);

void CloneGuardAim(struct AIMSTATE *paim, struct LO *ploBase) {
    CLo_Clone((struct LO *)paim, ploBase);
    CloneAnimref(&paim->animref);
}
