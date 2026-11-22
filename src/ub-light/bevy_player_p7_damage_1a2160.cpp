// SPDX-License-Identifier: GPL-3.0-or-later
#include "jtzap.h"
extern "C" void bevy_player_p7_damage_1a2160(JTZAP *pzap, ZAPXP *pxp)
{
    int state = pzap->state;
    if (state == 5) {
        pxp->field_0x34 = 0;
    } else if (state >= 6) {
        if (state < 0xD) {
            if (state >= 8)
                pxp->field_0x34 = 0;
        }
    }
    pxp->grf = pxp->grf | 1;
}
