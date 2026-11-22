// SPDX-License-Identifier: GPL-3.0-or-later
#include "vifunpacktable.h"
extern "C" {
void AddVifUnpack__4VIFS3UPKiPvi(void *, int, int, void *, int);

s32 func_001EC6D0(VIFUNPACKTABLE *table, s32 index, s32 iqw, void *pvifs) {
    s8 sp[0x10] __attribute__((aligned(16)));
    VIFUNPACKENTRY *entry = &table->aentry[index];
    *(s128 *)sp = entry->pdata->qw;
    AddVifUnpack__4VIFS3UPKiPvi(pvifs, 0xC, 1, sp, iqw);
    return 1;
}

}
