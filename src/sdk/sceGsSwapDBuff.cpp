/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct GSDISPENV {
    u8 unknown_0x0[0x28];
};
struct GSDRAWENV {
    u8 unknown_0x0[0xF0];
};
/* Two display environments (0x28 bytes each), then two drawing environments (0xF0 bytes each). */
struct GSDBUFF {
    GSDISPENV disp[2];
    GSDRAWENV draw[2];
};
extern "C" {
void sceGsPutDispEnv(GSDISPENV *env);
void sceGsPutDrawEnv(GSDRAWENV *env);
void sceGsSwapDBuff(GSDBUFF *buffers, s32 index) {
    s32 side;
    side = index & 1;
    sceGsPutDispEnv(&buffers->disp[side]);
    if (side != 0) {
        sceGsPutDrawEnv(&buffers->draw[1]);
        return;
    }
    sceGsPutDrawEnv(&buffers->draw[0]);
}
}
