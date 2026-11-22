// SPDX-License-Identifier: GPL-3.0-or-later
#include "coin.h"
#include "clock.h"

extern "C" {
void UpdateDprize(DPRIZE *pdprize, float dt);

void UpdateCoin(COIN *coin, float dt)
{
    UpdateDprize(coin, dt);
    if (coin->dprizes == 0) {
        coin->wait = coin->wait - g_2dded0.dt;
        if (coin->wait <= 0.0f)
            coin->SetDprizes(5);
    }
}
}
