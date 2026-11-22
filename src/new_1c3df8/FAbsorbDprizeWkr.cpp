// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

/* the ZPD SO::FAbsorbWkr (slot 75) takes: only its flags are read here */
struct ZPD {
    u8 unknown_0x0[0x44];
    /* 0x44 */ u32 grf;
};

extern "C" int FAbsorbDprizeWkr(DPRIZE *pdprize, ZPD *pzpd)
{
    if (pdprize->collectable != 0) {
        if (pzpd->grf & 8) {
            pdprize->SetDprizes(1);
            return 1;
        }
        return 0;
    }
    return 0;
}
