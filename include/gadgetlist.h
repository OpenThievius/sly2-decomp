/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GADGETLIST, the player's list of gadgets that the menu names (JT::pgadgetlist at 0xF38): func_002111F0 reads its count and its
   entries' string ids; func_00211148 asks it for the names of the first two (func_00202730, func_002026F8). Layout from
   func_002111F0 only. C++ only. */
#ifndef SLY2_GADGETLIST_H
#define SLY2_GADGETLIST_H
#include "types.h"

struct GADGETENTRY {
    u8 unknown_0x0[0xF8];
    /* 0xF8 */ s32 stringId;   /* func_002111F0 looks its text up with PchzStringFromId */
};

struct GADGETLIST {
    u8 unknown_0x0[0x74];
    /* 0x74 */ s32 count;      /* func_002111F0 */
    /* 0x78 */ GADGETENTRY *apentry[1];
};
#endif
