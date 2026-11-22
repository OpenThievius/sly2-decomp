/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "globset.h"
#include "factory.h"

/* MURRAY's constructor chain: SO's part, then the jumper at 0x1890 */
typedef struct NEWMURRAY {
    NEWSO so;
    u8 unknown_0x178[0x1890 - 0x178];
    u8 jumper[0x70];
} NEWMURRAY;

void *InitJumper(void *);
extern u8 D_002D44C8; /* MURRAY's vtable */
extern u8 D_002D9978; /* SO's vtable */

NEWMURRAY *ConstructMurray(NEWMURRAY *murray) {
    murray->so.basic.field_0x0 = 0;
    murray->so.basic.psidebag = 0;
    murray->so.basic.pvtbl = &D_002D9978;
    __7GLOBSET(&murray->so.globset);
    murray->so.field_0x174 = 0;
    murray->so.basic.pvtbl = &D_002D44C8;
    InitJumper(murray->jumper);
    return murray;
}
