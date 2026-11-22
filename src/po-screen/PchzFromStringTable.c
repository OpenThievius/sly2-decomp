/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct STRINGENTRY {
    s32 id;
    char *pch;
};
struct STRINGTABLE {
    s32 count;
    struct STRINGENTRY *entries;
};
extern char RO_002A8A98[];

char *PchzFromStringTable(struct STRINGTABLE *table, s32 id) {
    char *result;
    s32 count;
    s32 index;
    struct STRINGENTRY *entry;

    count = table->count;
    index = 0;
    if (count > 0) {
        entry = table->entries;
    next:
        index += 1;
        if ((id != entry->id) || (result = entry->pch, (result == 0))) {
            entry += 1;
            if (index >= count) {
                goto notfound;
            }
            goto next;
        }
    } else {
    notfound:
        result = RO_002A8A98;
    }
    return result;
}
