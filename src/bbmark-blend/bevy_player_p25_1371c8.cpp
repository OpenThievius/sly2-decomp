// SPDX-License-Identifier: GPL-3.0-or-later
#include "jtholder.h"
extern "C" int FAsegaGone(void *);
extern "C" void bevy_player_p25_1371c8(JTHOLDER *pholder)
{
    if (FAsegaGone(pholder->pjt->field_0x1030) != 0) {
        JT *pjt = pholder->pjt;
        pjt->SetMode(0);
    }
}
