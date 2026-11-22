/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "globset.h"
#include "factory.h"

/* SLY's constructor chain: SO's part, then the two words at 0x2044 */
typedef struct NEWSLY {
    NEWSO so;
    u8 unknown_0x178[0x2044 - 0x178];
    s32 field_0x2044;
    s32 field_0x2048;
} NEWSLY;

extern u8 D_002D2E98; /* SLY's vtable */
extern u8 D_002D9978; /* SO's vtable */

NEWSLY *ConstructSly(NEWSLY *sly) {
    sly->so.basic.field_0x0 = 0;
    sly->so.basic.psidebag = 0;
    sly->so.basic.pvtbl = &D_002D9978;
    __7GLOBSET(&sly->so.globset);
    sly->so.field_0x174 = 0;
    sly->so.basic.pvtbl = &D_002D2E98;
    sly->field_0x2044 = 0;
    sly->field_0x2048 = 0;
    return sly;
}
