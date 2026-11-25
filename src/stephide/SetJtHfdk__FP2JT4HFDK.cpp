// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct World { u8 unknown_0x0[0x1024]; int f1024; };
struct JTPART { World *world; u8 unknown_0x4[0x28]; int hfdk; float timer; int mode; u8 unknown_0x38[0x18]; int f50; u8 unknown_0x54[0x14]; int f68; };
enum HFDK { HFDK_NONE = 0 };
extern float g_2dded0;
void SetJtHfdk(JTPART *jt, HFDK hfdk)
{
    if (hfdk == jt->hfdk) return;
    jt->hfdk = hfdk; jt->f50 = 0; jt->timer = g_2dded0;
    if (hfdk > 0) { if (hfdk >= 3) { if (hfdk == 3) jt->mode = 1; } else { if (jt->world->f1024 == jt->f68) jt->mode = 2; else jt->mode = 0; } }
}
