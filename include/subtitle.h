/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SUBTITLE, the on-screen subtitle record of the movie text: a stream id, a colour and a set of flags. Its functions of src/new_2271f8:
   func_00227788 resets it (-1, the colour of kind -1, 0), func_00227728 sets the id and a colour kind, func_002277D0 looks the id up
   in the world's string table, func_00227820 follows the stream named by sid, func_00227940 spells grf out. Three readers agree on
   each field. C and C++. */
#ifndef SLY2_SUBTITLE_H
#define SLY2_SUBTITLE_H
#include "types.h"

/* A four-byte colour returned by value: func_002275B8 receives its result through a hidden pointer, which a user-declared
   constructor gives it under g++ 2.95 (see func_00227728). */
struct Color4 {
    u8 channel[4];
#ifdef __cplusplus
    Color4() {}
#endif
};

struct SUBTITLE {
    /* 0x0 */ s32 sid;      /* the stream or string id, -1 when none: func_00227788 sets it, func_00227728, func_002277D0, func_00227820 read it */
    /* 0x4 */ struct Color4 color; /* func_00227788 and func_00227728 set it from func_002275B8 (copied byte-aligned) */
    /* 0x8 */ u32 grf;      /* func_00227788 clears it; func_00227940 tests its bits */
};
#endif
