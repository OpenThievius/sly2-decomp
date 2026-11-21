/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BRK, a breakable: derived from LO (include/lo.h). The fields are read by its own functions AddBrkTouchObject and
   AddBrkTouchClass (the PloFindSpawn file, 0x227FE8); the same count-and-four-entries layout as SPAWN from 0x148. C++ only:
   AddBrkTouchObject__FP3BRK3OID takes the OID enum. */
#ifndef SLY2_BRK_H
#define SLY2_BRK_H
#include "lo.h"

/* A breakable: the objects and classes that set it off when they touch it (a count and four entries each). */
enum OID { OID_none };

struct BRKTOUCH {
    int oid;
    int data;
};

struct BRK : LO {
    u8 unknown_0x50[0x148 - 0x50];
    /* 0x148 */ unsigned ctouch;       /* AddBrkTouchObject */
    /* 0x14C */ BRKTOUCH atouch[4];    /* AddBrkTouchObject */
    /* 0x16C */ unsigned ccid;         /* AddBrkTouchClass */
    /* 0x170 */ int acid[4];           /* AddBrkTouchClass */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(BRK, ctouch, 0x148);
SLY2_OFFSET_CHECK(BRK, ccid, 0x16C);
#endif
#endif
