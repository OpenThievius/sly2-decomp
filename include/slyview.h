/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C view of the parts of SLY (sly.h, C++ only) and its gadget slot that the player code written in C reads, at the offsets of
   sly.h and jt.h. A field sly.h lacks is here only, with its readers. A C++ source uses SLY itself. C only. */
#ifndef SLY2_SLYVIEW_H
#define SLY2_SLYVIEW_H
#ifdef __cplusplus
#error "slyview.h is the C view of sly.h: include sly.h in C++"
#endif
#include "types.h"

struct LO;

/* one of the player's gadget slots (jt.h GADGETSLOT) */
struct GADGETSLOTVIEW {
    /* 0x0 */ s32 gadget;
    /* 0x4 */ void *ppool;
    /* 0x8 */ struct LO *plo; /* func_0018D698 subscribes to it and unsubscribes from the old one */
};

struct SLYVIEW {
    u8 unknown_0x0[0x18C8];
    /* 0x18C8 */ s32 jts; /* SLY::jts: the player's state (func_0018A238 tests 3) */
    u8 unknown_0x18CC[0x118];
    /* 0x19E4 */ void *alookat[5]; /* SetJtLookats: look-at actors, set by bits 0 to 4 of its mask; UpdateJtStand and func_00189618 read the same words */
    /* 0x19F8 */ void *plookatBit6; /* SetJtLookats: bit 6 */
    /* 0x19FC */ void *plookatBit5; /* SetJtLookats: bit 5 */
    u8 unknown_0x1A00[0x330];
    /* 0x1D30 */ s32 field_0x1D30; /* bevy_player_p13_18df50 sets it; func_00188F20, func_0018A8C8, func_0018D760 and func_0018C250 read it */
    u8 unknown_0x1D34[0x26C];
    /* 0x1FA0 */ s128 rideOffset; /* SetJtRideOffset */
    u8 unknown_0x1FB0[0xB0];
};

#if defined(__mips__)
typedef char check_SLYVIEW_size[(sizeof(struct SLYVIEW) == 0x2060) ? 1 : -1];
typedef char check_SLYVIEW_rideOffset[((unsigned int)&((struct SLYVIEW *)0)->rideOffset == 0x1FA0) ? 1 : -1];
typedef char check_SLYVIEW_plookatBit5[((unsigned int)&((struct SLYVIEW *)0)->plookatBit5 == 0x19FC) ? 1 : -1];
#endif
#endif
