/* SPDX-License-Identifier: GPL-3.0-or-later */
/* PMF, a pointer to member function as g++ 2.95 stores it: 8 bytes, 4-aligned, so its readers copy a constant one with an ldl/ldr
   pair (Splat then labels its last byte). QueueSwCallback stores one in a CB; CancelSwCallbacks compares index, then pfn, or only
   its low half (delta2) when index is not -1; UpdateSwCallbacks calls it as a C++ pointer to member (`void (OBJ::*)(int)`); ZapContinue
   adds delta to the object and calls pfn when index is not 0. MCPMF (memcard.h) is the same layout. */
#ifndef SLY2_PMF_H
#define SLY2_PMF_H
#include "types.h"

typedef struct PMF {
    /* 0x0 */ s16 delta; /* added to the object's address before the call */
    /* 0x2 */ s16 index; /* -1: pfn is the function itself; 0: a null pointer; else the virtual function's vtable index */
    /* 0x4 */ union {
        void (*pfn)(); /* index -1 */
        s16 delta2;    /* a virtual function: the offset of the vtable pointer in the object (0xC in Sly 2's classes) */
    } pfn_or_delta2;
} PMF;

#endif
