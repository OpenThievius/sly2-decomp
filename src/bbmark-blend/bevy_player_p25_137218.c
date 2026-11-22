/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtholder.h"

void func_002046F0(struct JTVIEW *pjt, sptr pguard);

void bevy_player_p25_137218(struct JTHOLDER *pholder) {
    struct JTVIEW *pjt;
    sptr pguard;

    pjt = pholder->pjt;
    pguard = pjt->field_0x10DC;
    if (pguard != 0) {
        func_002046F0(pjt, pguard);
    }
}
