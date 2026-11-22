// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"
#include "clock.h"

extern "C" {
void UpdateDprize(DPRIZE *, float dt);

// UpdateDprizeCharm: the same body as UpdateDprizeCoin
void func_001C6880(DPRIZECHARM *pcharm, float dt)
{
    UpdateDprize(pcharm, dt);
    if (pcharm->dprizes == 0) {
        pcharm->wait = pcharm->wait - g_2dded0.dt;
        if (pcharm->wait <= 0.0f)
            pcharm->SetDprizes(5);
    }
}
}
