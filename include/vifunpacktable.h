/* SPDX-License-Identifier: GPL-3.0-or-later */
/* VIFUNPACKTABLE: the shader list func_001EC688 and func_001EC6D0 index (8-byte entries at 0x20; our names, from what the two read). */
#ifndef SLY2_VIFUNPACKTABLE_H
#define SLY2_VIFUNPACKTABLE_H
#include "types.h"

struct VIFUNPACKDATA {
    u8 unknown_0x0[0x30];
    /* 0x30 */ s128 qw; /* func_001EC6D0 unpacks this quadword */
};

struct VIFUNPACKENTRY {
    /* 0x0 */ s32 count;          /* func_001EC688 passes it as AddVifUnpack's count */
    /* 0x4 */ VIFUNPACKDATA *pdata; /* func_001EC688 passes it on, func_001EC6D0 reads 0x30 of it */
};

struct VIFUNPACKTABLE {
    u8 unknown_0x0[0x20];
    /* 0x20 */ VIFUNPACKENTRY *aentry; /* both functions index it */
};
#endif
