/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RUMBLE, a controller's rumble state, 0x1C bytes (retail's P6RUMBLE in InitRumble__FP6RUMBLEii, UpdateRumble__FP6RUMBLE): JOY::rumble
   (joy.h) holds one. Field names as UpdateRumble and func_001D51B8 name them (Sly 1's RUMBLE, sly1 include/rumble.h, CC0); InitRumble
   (a method of the class) stores nPort and nSlot and tests rums. C and C++. */
#ifndef SLY2_RUMBLE_H
#define SLY2_RUMBLE_H
#include "types.h"

struct RUMPAT;

struct RUMBLE {
    /* 0x0 */ s32 nPort;
    /* 0x4 */ s32 nSlot;
    /* 0x8 */ s32 rums;
    /* 0xC */ struct RUMPAT *prumpat;
    /* 0x10 */ s32 irumins;
    /* 0x14 */ f32 dtRumble;
    /* 0x18 */ f32 dtRumins;
};

#if defined(__mips__)
typedef char check_RUMBLE_size[(sizeof(struct RUMBLE) == 0x1C) ? 1 : -1];
#endif
#endif
