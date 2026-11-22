// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"
#include "sw.h"
#include "clock.h"

extern "C" {
extern SW B_003DD490;
int func_001C4BD8(SW *psw, int cpmagnetMax, void **apmagnet);
int func_001C5B20(DPRIZE *pdprize, void *pmagnet);
int FIsBasicDerivedFrom(void *, int);
}

void CheckDprizeCollect(DPRIZE *pdprize)
{
    if (pdprize->collectable == 0)
        return;
    if (pdprize->tExpire < g_2dded0.t) {
        pdprize->SetDprizes(1);
        return;
    }
    void *apmagnet[16];
    int cpmagnet = func_001C4BD8(&B_003DD490, 16, apmagnet);
    void **ppmagnet = apmagnet;
    for (int ipmagnet = 0; ipmagnet < cpmagnet; ppmagnet++, ipmagnet++) {
        if (ipmagnet > 0) {
            if (FIsBasicDerivedFrom(pdprize, 0x5B) == 0)
                break;
        }
        if (func_001C5B20(pdprize, *ppmagnet) == 0)
            continue;
        break;
    }
}
