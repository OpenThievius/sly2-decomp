// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"

/* The binocular recon screen (the bevy_ui_binoc_recon functions; bevy_ui_binoc_recon_202768 has the fields it switches on). */
struct BINOCRECON {
    /* 0x0 */ s32 state;
    u8 unknown_0x4[0xC];
    /* 0x10 */ f32 pos[3];          /* func_00201D78: a screen position, x mapped from -1..1 to 0..640, y 246.4 */
    u8 unknown_0x1C[0x8C];
    /* 0xA8 */ LO **pplo;           /* the focus object */
};

extern "C" void func_00201D78(BINOCRECON *arg0, LO **arg1)
{
    f32 *tail = arg0->pos;
    float oldField10;
    float oldField14;
    arg0->pos[0] = 0.0f;
    arg0->pplo = arg1;
    ((int *)tail)[1] = 0;
    ((int *)tail)[2] = 0;
    oldField10 = arg0->pos[0];
    oldField14 = tail[1];
    arg0->pos[0] = (oldField10 * 320.0f) + 320.0f;
    tail[1] = 246.40001f;
    tail[2] = oldField14;
    arg0->state = -1;
}
