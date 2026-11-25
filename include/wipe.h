/* SPDX-License-Identifier: GPL-3.0-or-later */
/* WIPE, the screen-wipe object: an SO (include/so.h) whose own fields start at 0x150; InitWipe, PostWipeLoad, UpdateWipeState and
   SetWipeState are its methods. C++ only. */
#ifndef SLY2_WIPE_H
#define SLY2_WIPE_H
#include "so.h"

struct ASEGA;

struct WIPE : SO {
    /* 0x150 */ s32 wipes;      /* the wipe's state (-1 off): InitWipe and PostWipeLoad set -1, UpdateWipeState switches on it, SetWipeState */
    /* 0x154 */ f32 tWipes;     /* the clock time of the last change: SetWipeState */
    u8 unknown_0x158[0x8];      /* filled by SetSoProperties from the list at 0x2BD380 (offsets 0x158 and 0x15C) */
    /* 0x160 */ struct ASEGA *pasega; /* the wipe's animation: UpdateWipeState (FAsegaGone, ReleaseAsegaHandle), SetWipeState (master speed) */
    /* 0x164 */ s32 field_0x164; /* readers: HandleWipeMessage (a WIPE method; messages 0x5FB and 0x5FC set it to 1 and 0), StartWipe sets 1 (two functions agree) */
    /* 0x168 */ s32 field_0x168; /* the same, messages 0x5FD and 0x5FE */
    /* 0x16C */ s32 field_0x16C; /* HandleWipeMessage (0x5FF clears it, 0x600 sets it), StartWipe sets 1 */
    /* 0x170 */ s32 hstream;    /* the stream UpdateWipeState waits for in state 3 (FStreamPlaying); HandleWipeMessage tests it against -1 */
};
#endif
