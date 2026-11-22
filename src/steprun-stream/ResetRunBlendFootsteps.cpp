// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"

// a run blend (named after ResetRunBlendFootsteps, its only reader here)
struct RUNBLEND {
    u8 unknown_0x0[0x9C];
    s32 field_0x9C;
    s32 field_0xA0;
};

void ResetRunBlendFootsteps(RUNBLEND *prunbl)
{
    prunbl->field_0xA0 = 0;
    prunbl->field_0x9C = 0;
}
