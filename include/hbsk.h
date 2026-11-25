/* SPDX-License-Identifier: GPL-3.0-or-later */
/* HBSK, the object src/hide/ builds (InitHbsk, OnHbskAdd, OnHbskRemove, CloneHbsk, PresetHbskAccel, SetHbskHbsks, FAbsorbHbskWkr): an SO
   (0x150 bytes, include/so.h) that carries a MEMBER (include/pzo_hide.h) at 0x150, because InitHbsk hands its address to the MEMBER
   initialiser bevy_player_p6_182c70, then a DLE at 0x174 (OnHbskAdd and OnHbskRemove put the object into the list B_003E13E4, which
   keeps the entry there, CloneHbsk saves the 8 bytes across the base clone), the state at 0x17C, a flag at 0x18C and the player it
   works with at 0x190. Names hbsks and fLocked follow SetHbskHbsks (src/hide-splice-gc/), which reads the same two offsets. Every
   field below is read by a method of the class. In C (the C files of src/hide/) SO is not available: the same fields follow 0x150
   bytes of unknown. C and C++. */
#ifndef SLY2_HBSK_H
#define SLY2_HBSK_H
#include "pzo_hide.h"
#include "dl.h"
#include "wkr.h"

struct JT;

#define HBSK_FIELDS \
    /* 0x150 */ struct MEMBER member; /* InitHbsk passes its address to bevy_player_p6_182c70, then sets member.field_0x8 to 300.0 */ \
    /* 0x174 */ struct DLE dle;       /* OnHbskAdd, OnHbskRemove: the list B_003E13E4 has ibDle 0x174; CloneHbsk keeps it across the clone */ \
    /* 0x17C */ s32 hbsks;            /* the state: InitHbsk, OnHbskPoolClaim clear it; PresetHbskAccel tests it; FAbsorbHbskWkr, SetHbskHbsks */ \
    /* 0x180 */ f32 uFade;           /* SetHbskHbsks stores the clock when the state changes */ \
    u8 unknown_0x184[0x8]; \
    /* 0x18C */ s32 fLocked;          /* InitHbsk sets 1; PresetHbskAccel tests it */ \
    /* 0x190 */ struct JT *pjt;       /* FAbsorbHbskWkr (SO slot 75 of the class) reads the player's binoculars through it */

#ifdef __cplusplus
#include "so.h"
struct HBSK : SO {
    HBSK_FIELDS
};
#else
struct HBSK {
    u8 unknown_0x0[0x150];
    HBSK_FIELDS
};
#endif

/* WKR, the weapon record FAbsorbHbskWkr takes: wkr.h */
#endif
