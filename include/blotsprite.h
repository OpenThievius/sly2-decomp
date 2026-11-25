/* SPDX-License-Identifier: GPL-3.0-or-later */
/* A movie blot's sprites (BLOT::asprite points at an array of BLOT::csprite of them): each has a list of labels (0x18 bytes, the
   label id at 0x14), a list of instances (0x18 bytes, the state at 8, -1 when unused) and a transform pair a blot's font fills in
   (func_00213CD8). Readers: SeekBlotLabel, func_00212F80, func_00213CD8 (all three agree on the 0x30-byte layout). C++ only. */
#ifndef SLY2_BLOTSPRITE_H
#define SLY2_BLOTSPRITE_H
#include "types.h"
struct BLOTSPRITELABEL {
    u8 unknown_0x0[0x14];
    s32 id;
};
struct BLOTSPRITEINSTANCE {
    u8 unknown_0x0[0x8];
    s16 state;
    u8 unknown_0xA[0xE];
};
struct BLOTSPRITE {
    u16 clabel;
    u16 cinstance;
    BLOTSPRITELABEL *alabel;
    BLOTSPRITEINSTANCE *ainstance;
    u8 unknown_0xC[0x20];
    QW *transform;
};
#endif
