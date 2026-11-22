/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CLASSINFO, one record of retail's class table: 0x14 bytes per class, from 0x2BAAE8 (class 0, the root) to 0x2BBA74, indexed
   by class id (func_001ED7A8 calls D_002BAAE8[cid].pfnCreate; config/recovered/class_diff.tsv lists the classes). Each class's
   Slot6 virtual (lo.h) returns the address of its record: those are the getters of new_100008 (0x113A10 to 0x114580,
   PvtGetCidB1 to B7 among them). The words, from the table's data (src/data/new_100008_2ba*.cpp) and the readers:
   +0x00 pclassinfoParent: the parent class's record, 0 for the root (D_002BAB24, class 3, holds D_002BAB10, class 2 = LO);
   +0x04 cid: the class id (PeopidFind reads it at +4);
   +0x08 unknown_0x8: 199 in the root, cid + 1 for a leaf (30 for 29, 34 for 33), 48 for class 3: it looks like one past the
         last class id of the class's subtree, not proven;
   +0x0C cb: the instance's size (16 for the root, 0xE0 for class 3, as class_diff.tsv; func_001ED850 copies cb bytes);
   +0x10 pfnCreate: the class's factory (func_001ED850 and func_001ED7A8 call it; the factories of new_100008 return the new
         instance as void *). C and C++. */
#ifndef SLY2_CLASSINFO_H
#define SLY2_CLASSINFO_H
#include "types.h"

typedef struct CLASSINFO {
    /* 0x00 */ struct CLASSINFO *pclassinfoParent;
    /* 0x04 */ s32 cid;
    /* 0x08 */ s32 unknown_0x8;
    /* 0x0C */ s32 cb;
    /* 0x10 */ void *(*pfnCreate)(void);
} CLASSINFO;

#if defined(__mips__)
typedef char check_CLASSINFO_size[(sizeof(CLASSINFO) == 0x14) ? 1 : -1];
#endif
#endif
