// SPDX-License-Identifier: GPL-3.0-or-later
#include "rip.h"
#include "clock.h"
extern "C" {
extern QW D_002C1F50;
extern QW RO_002A2D00[3];

void InitRip__FP3RIPP6VECTORfP2SO(RIP *rip, QW pos, float field_0x20, SO *psoTouch) {
    rip->tStart = g_2dded0.t;
    rip->dtLifetime = 1.0f;
    rip->psoTouch = psoTouch;
    rip->field_0x20 = field_0x20;
    rip->field_0x30 = D_002C1F50;
    rip->posPrev = pos;
    rip->pos = pos;
    rip->field_0x40 = RO_002A2D00[0];
    rip->field_0x50 = RO_002A2D00[1];
    rip->field_0x60 = RO_002A2D00[2];
}

}
