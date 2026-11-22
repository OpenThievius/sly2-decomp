/* SPDX-License-Identifier: GPL-3.0-or-later */
/* A node of one of the GC pools (pair, varb, frame, proc, sidebag, ...): a reference count, then two links packed as chunk and
   index within the pool, then a generation bit. Layout from the Link*Node functions (they write prev and next: func_00255248,
   func_00255588, func_002558C0, func_00255C00, func_00255F38) and the Init*Node functions (they write cref and gen). C and C++. */
#ifndef SLY2_GCNODE_H
#define SLY2_GCNODE_H
#include "types.h"
typedef struct GNODE {
    s32 cref;
    u32 prevIndex : 13;
    u32 prevChunk : 2;
    u32 unused : 1;
    u32 nextIndex : 13;
    u32 nextChunk : 2;
    u32 gen : 1;
} GNODE;
#endif
