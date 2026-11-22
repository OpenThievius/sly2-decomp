// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"
#include "clock.h"

extern "C" {
void UpdateDprize(DPRIZE *, float dt);

// UpdateDprizeCoin: the base update, then the rest countdown of state 0 ends in state 5
void func_001C6588(DPRIZECOIN *pcoin, float dt)
{
    UpdateDprize(pcoin, dt);
    if (pcoin->dprizes == 0) {
        pcoin->wait = pcoin->wait - g_2dded0.dt;
        if (pcoin->wait <= 0.0f)
            pcoin->SetDprizes(5);
    }
}
}
