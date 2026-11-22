/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "soview.h"

void AdjustSoMomint__FP2SOf(struct SOVIEW *, f32);

void SetSoMass__FP2SOf(struct SOVIEW *pso, f32 mass) {
    struct PHYSVIEW *pphys;
    f32 massOld;
    f32 ratio;

    pphys = pso->pphys;
    massOld = pphys->field_0xD0;
    ratio = mass / massOld;
    pphys->field_0xD0 = (f32) (massOld * ratio);
    AdjustSoMomint__FP2SOf(pso, ratio);
}
