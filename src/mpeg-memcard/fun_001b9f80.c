/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "guardview.h"

void InitGuard(void);

/* the init of ZONEGUARD (class 60, stepguard.h; slot 7): its C view is guardview.h's ZONEGUARDVIEW */
void func_001B9F80(struct ZONEGUARDVIEW *pguard) {
    f32 *pcurve;

    InitGuard();
    pcurve = pguard->curve;
    pcurve[0] = 1.35f;
    pcurve[1] = -0.0003f;
    pcurve[2] = 0.0f;
    pguard->lowLimit = 0.9f;
    pguard->highLimit = 1.2f;
    pguard->reach = 7.0f;
    pguard->guard.field_0x364 = 0;
    pguard->guard.sensing = 0;
    pguard->guard.psensor->grfSensing = 3;
    pguard->guard.field_0x4A4 = 1;
}
