/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The two script-heap node types PsidebagNew and PvarbNew allocate from their slot heaps (B_00452148, B_004520D0): a GNODE (reference
   count, pool links, generation: include/gcnode.h) first. A sidebag holds its first varb at 0x8 (PsidebagNew clears it); a varb holds
   a CRef at 0xC (PvarbNew sets its tag to TAGK_Nil) and the next varb at 0x14 (PvarbNew clears it; VarbPtr_Assign destroys it). C++ */
#ifndef SLY2_SIDEBAG_H
#define SLY2_SIDEBAG_H
#include "cref.h"
#include "gcnode.h"

struct VARB;

struct SIDEBAG {
    GNODE node;
    VARB *pvarb;
};

struct VARB {
    GNODE node;
    u8 unknown_0x8[0x4];
    CRef ref;
    VARB *pvarbNext;
};
#endif
