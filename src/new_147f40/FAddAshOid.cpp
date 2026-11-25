// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "button.h"
extern "C" {
s32 FAddAshOid(ASHLIST *pashlist, s32 oid, s32 nArg) {
    u32 index = pashlist->count;
    if (index >= 8) {
        return 0;
    }
    pashlist->aentry[index].oid = oid;
    pashlist->aentry[pashlist->count].nArg = nArg;
    pashlist->count += 1;
    return 1;
}
}
