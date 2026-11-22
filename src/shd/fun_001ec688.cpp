// SPDX-License-Identifier: GPL-3.0-or-later
#include "vifunpacktable.h"

extern "C" {
void AddVifUnpack__4VIFS3UPKiPvi(void *pvifs, s32 cqw, s32 count, void *pdata, s32 iqw);

s32 func_001EC688(VIFUNPACKTABLE *table, s32 index, s32 iqw, void *pvifs) {
    VIFUNPACKENTRY *entry = &table->aentry[index];
    AddVifUnpack__4VIFS3UPKiPvi(pvifs, 0xC, entry->count, entry->pdata, iqw);
    return entry->count;
}

}
