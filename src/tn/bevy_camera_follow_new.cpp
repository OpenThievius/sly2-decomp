// SPDX-License-Identifier: GPL-3.0-or-later
#include "cplcy.h"
extern "C" {
void CPLCY_Destruct(CPTN *);
extern float D_002C41A8[2];

void bevy_camera_follow_new(CPTN *cptn) {
    CPLCY_Destruct(cptn);
    D_002C41A8[0] = -3.4028235e38f;
    D_002C41A8[1] = 3.4028235e38f;
    cptn->ptn = 0;
    cptn->ptnfn = 0;
}
}
