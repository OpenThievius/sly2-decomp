// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" {
void ActivateAmb(AMB *);
void DeactivateAmb(AMB *);

void SetAmbGrf(AMB *pamb, s32 grfMask, s32 grfValue)
{
    s32 mask;
    s32 value;
    u16 grf;

    mask = grfMask & 0xFFFF;
    value = (u16)grfValue & mask;
    grf = (pamb->grf & ~mask) | value;
    pamb->grf = grf;
    if (grf != 0) {
        ActivateAmb(pamb);
        return;
    }
    DeactivateAmb(pamb);
}
}
