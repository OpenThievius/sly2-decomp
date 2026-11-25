// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
#include "sly2.h"
#include "ps2inline.h"

extern "C" {
int FFloatsNear__Ffff(float, float, float);
void SetAmbGrf(AMB *, int, int);
}
extern QW g_2a2dd0;

static inline int Near(float first, float second) { return FFloatsNear__Ffff(first, second, 0.0001f); }

void SetAmbPos(AMB *pamb, QW pos)
{
    pamb->pos = pos;
    QW origin = g_2a2dd0;
    int atOrigin = 0;
    if (Near(LaneX(origin), LaneX(pos))) {
        float originY = LaneYInGeneralRegister(origin);
        float posY = LaneYInGeneralRegister(pos);
        if (Near(originY, posY)) {
            float originZ = LaneZInGeneralRegister(origin);
            float posZ = LaneZInGeneralRegister(pos);
            atOrigin = Near(originZ, posZ) != 0;
        }
    }
    if (atOrigin == 0) {
        SetAmbGrf(pamb, 0x200, 0x200);
    } else if (pamb->palo == 0) {
        SetAmbGrf(pamb, 0x200, 0);
    }
}
