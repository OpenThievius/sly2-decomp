// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
#include "soproperty.h"
extern "C" {
void LoadStepFromBrx(STEP *step);
void SetSoProperties(SO *so, s32 count, SOPROPERTY *properties);
extern SOPROPERTY D_002BE990[173];

void LoadSlyFromBrx(SLY *sly) {
    LoadStepFromBrx(sly);
    VECTOR *vec = &sly->vecLocal;
    vec->x = 0.0f;
    vec->y = 0.0f;
    vec->z = -75.0f;
    SetSoProperties(sly, 0xAD, D_002BE990);
}

}
