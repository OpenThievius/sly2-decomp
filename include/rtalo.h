/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RTALO: the object func_001BEB28 (RtAlo_Show_thunk) and its neighbours handle (src rog-path, vtable at 0xC): up to four children and
   a pointer into the window array at 0x3E1A78. Layout from func_001BEE60 (count, children, window) and func_001BEE10 (window);
   func_001BEB28 reads the same words with a local type. C++ only. */
#ifndef SLY2_RTALO_H
#define SLY2_RTALO_H
#include "so.h"
#include "lo.h"
#include "rogwindow.h"

struct RTALO : LO {
    u8 unknown_0x50[0x90];
    /* 0xE0 */ s32 count;      /* how many children are set: func_001BEE60 */
    /* 0xE4 */ SO *apso[4];    /* the children: func_001BEE60 passes the address of each one's field_0x80 (SO's globset) */
    /* 0xF4 */ u32 aflag[4];   /* per child: bit 0 set when func_001BEB28 added it, bit 1 when it called its slot 21 with 0; func_001BED18 undoes them (readers: func_001BEB28, func_001BED18) */
    u8 unknown_0x104[0x24];
    /* 0x128 */ ROGWINDOW *pwindow; /* the window it sits in, an element of B_003E1A78: func_001BEE10 indexes a table with its position, func_001BEE60 tests it */
};
#endif
