/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct AMB_PAN { u8 unknown_0x0[0x14]; s32 pan; };

void SetAmbGrf(struct AMB_PAN *pamb, s32 grfMask, s32 grfValue);

void SetAmbPan(struct AMB_PAN *pamb, s32 degrees)
{
    s32 remainder;
    s32 pan;

    remainder = degrees % 360;
    pan = (remainder > -1) ? remainder : (remainder + 0x168);
    if (pan != pamb->pan) {
        pamb->pan = pan;
        SetAmbGrf(pamb, 0x20, 0x20);
    }
}
