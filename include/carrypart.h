/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CARRYPART: the carry part InitJt starts in the attachment at JT + 0x900 (JT::PvAttachCarry, include/jt.h; its Carry_* methods and
   func_001CC9A8, func_001CD308 take it). Only the words this module's small functions use; Carry_Attach_file.cpp has its own local
   CARRY with the others (pjt at 0, source at 0x34, the acts at 0x94 to 0x9C, the attached object at 0xA0). Not include/carry.h's CARRY
   (an LO). C and C++. */
#ifndef SLY2_CARRYPART_H
#define SLY2_CARRYPART_H
#include "types.h"

struct LO;
struct SO;
struct JT;

struct CARRYPART {
    /* 0x0 */ struct JT *pjt;   /* Carry_Attach (the carry part's method): the player it hangs on */
    u8 unknown_0x4[0x30];
    /* 0x34 */ struct LO *source; /* Carry_Attach: the object whose slot 32 gives the transform the carried object is parented to */
    u8 unknown_0x38[0x4C];
    /* 0x84 */ struct LO *plo;  /* func_001CC9A8: func_001A5BF0 resolves it to its owning SO */
    u8 unknown_0x88[0x8];
    /* 0x90 */ s32 field_0x90;  /* Carry_Init sets -1 */
    /* 0x94 */ void *act94;    /* Carry_Attach, Carry_Detach, func_001CD308 (methods of the part): the acts that hold the carried object, released together */
    /* 0x98 */ void *act98;
    /* 0x9C */ void *act9C;
    /* 0xA0 */ struct SO *attached; /* the carried object: Carry_Attach sets it, Carry_Detach and func_001CD308 clear it */
    /* 0xA4 */ s32 state;       /* Carry_Init sets -1; func_001CC9A8 tests 1 (guess: a state word) */
};

/* what Carry_SDistStartCurves and Carry_SDistEndCurves take: the carry in the first word and a flat position at 0x10 */
struct CARRYPROBE {
    struct CARRYPART *pcarry;
    u8 unknown_0x4[0xC];
    /* 0x10 */ QW posFlat;
};
#endif
