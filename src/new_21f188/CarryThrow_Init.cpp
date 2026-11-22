// SPDX-License-Identifier: GPL-3.0-or-later
#include "carrythrow.h"

void CarryThrow_Init(CARRYTHROW *pcarry, JT *pjtOwner)
{
    CARRYVECTOR *pomega = &pcarry->omega;
    CARRYVECTOR *pvecAim = &pcarry->vecAim;
    CARRYVECTOR *pvecLaunch = &pcarry->vecLaunch;
    pcarry->pjtOwner = pjtOwner;
    pcarry->state = -1;
    pcarry->field_0x1C = 500.0f;
    pcarry->field_0x20 = 1500.0f;
    pcarry->field_0x24 = 1.5f;
    pcarry->field_0x18 = pcarry->field_0x14 = 1.0f;
    pcarry->field_0x28 = 1000.0f;
    pomega->f[0] = 0.0f;
    pomega->f[1] = 0.0f;
    pomega->f[2] = 25.0f;
    pvecAim->f[0] = 1000.0f;
    pvecAim->f[1] = 0.0f;
    pvecAim->f[2] = 0.0f;
    pvecLaunch->f[0] = 42.0f;
    pvecLaunch->f[1] = -73.0f;
    pvecLaunch->f[2] = -50.0f;
}
