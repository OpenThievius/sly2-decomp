/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Two curve classes (CRV, crv.h; class 10 of retail's class table, 0x190 bytes) that carry the MEMBER block at 0x190 the curve
   attachments carry too (pzo_hide.h ATTACHCRV) and keep 8 bytes at 0x1B4 across CloneCrv:
   PIPE, a pipe the player rides along (class 11, 0x1E0 bytes, vtable 0x2D56F8; Sly 1's PIPE): InitPipe (slot 7) passes the MEMBER to
   its initialiser bevy_player_p6_182c70 and sets the fields below, ClonePipe keeps `kept` around CloneCrv.
   CRV13, class 13 (0x1D0 bytes, vtable 0x2D6FE8; its role is not recovered: an agent named its slots Pipe_AddLoGrfEntry (24) and
   Pipe_RemoveLoGrfEntry (23), but PIPE is class 11): func_001CB908 is its Init (slot 7), func_001CBA20 its Clone (slot 41).
   A field set by the class's own Init is certain with one reader. C++ only. */
#ifndef SLY2_PIPE_H
#define SLY2_PIPE_H
#include "types.h"
#include "crv.h"
#include "pzo_hide.h"

struct PIPE : CRV {
    u8 unknown_0x180[0x10];
    /* 0x190 */ MEMBER member;      /* InitPipe; its field_0x1C (0x1AC) is set to 1 after the initialiser's 7 */
    /* 0x1B4 */ BYTES8 kept;        /* ClonePipe saves it around CloneCrv */
    u8 unknown_0x1BC[0x4];
    /* 0x1C0 */ QW field_0x1C0;     /* InitPipe copies g_2a2da0 */
    /* 0x1D0 */ s32 field_0x1D0;    /* InitPipe sets 8 */
    /* 0x1D4 */ s32 field_0x1D4;    /* InitPipe sets 9 */
};

struct CRV13 : CRV {
    u8 unknown_0x180[0x10];
    /* 0x190 */ MEMBER member;      /* func_001CB908 starts it (bevy_player_p6_182c70) */
    /* 0x1B4 */ BYTES8 kept;        /* func_001CBA20 keeps it across the base clone */
    u8 unknown_0x1BC[0x4];
    /* 0x1C0 */ f32 field_0x1C0;    /* func_001CB908 sets 1000 */
    /* 0x1C4 */ f32 field_0x1C4;    /* func_001CB908 sets 1 */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(PIPE, member, 0x190);
SLY2_OFFSET_CHECK(PIPE, kept, 0x1B4);
SLY2_OFFSET_CHECK(PIPE, field_0x1D4, 0x1D4);
SLY2_OFFSET_CHECK(CRV13, member, 0x190);
SLY2_OFFSET_CHECK(CRV13, kept, 0x1B4);
SLY2_OFFSET_CHECK(CRV13, field_0x1C4, 0x1C4);
#endif
#endif
