/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct CMDENTRY {
    s32 kind;
    s32 value;
    u8 unknown_0x8[0x14];
};
struct CMDQUEUE {
    u8 unknown_0x0[0x50];
    s32 count;
    struct CMDENTRY *entries;
};

void func_00173358(struct CMDQUEUE *queue, s32 value) {
    s32 index = queue->count;
    struct CMDENTRY *entry;
    if (index < 0x80) {
        queue->count = index + 1;
        entry = &queue->entries[index];
        entry->kind = 2;
        entry->value = value;
    }
}
