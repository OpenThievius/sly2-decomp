/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"
#include "soview.h"

void func_001F5988(void *pso, void *psoDiscarded);

void func_00204C60(struct STEPVIEW *pstep, struct SO *psoDiscarded) {
    struct SOVIEW *psoSurface;

    func_001F5988(pstep, psoDiscarded);
    psoSurface = (struct SOVIEW *)pstep->psoSurface;
    if ((psoSurface != 0) && (psoSurface->field_0x48 == (s32)psoDiscarded)) {
        pstep->psoSurface = 0;
    }
}
