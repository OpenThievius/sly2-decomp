/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "heapalloc.h"
#include "sly2.h"
struct ENTRY { unsigned key; int unknown_0x4; int unknown_0x8; ENTRY *next; };
struct HASHTABLE { int count; ENTRY **buckets; int unk8; HEAPALLOC *alloc; };
void HashTable_Resize(HASHTABLE *table, int newCount)
{
    ENTRY *cur; ENTRY *chain; int index; cur = chain = 0;
    for (index = 0; index < table->count; index++) {
        cur = table->buckets[index];
        if (cur) {
            while (cur->next) cur = cur->next;
            cur->next = chain;
            chain = table->buckets[index];
        }
    }
    table->count = newCount;
    HEAPALLOC *alloc = table->alloc;
    void *fresh = alloc->Realloc(table->buckets, newCount << 2, 3);
    table->buckets = (ENTRY **)fresh;
    memset(fresh, 0, table->count << 2);
    cur = chain;
    while (cur) {
        ENTRY *next = cur->next;
        unsigned slot = cur->key % table->count;
        cur->next = table->buckets[slot];
        table->buckets[slot] = cur;
        cur = next;
    }
}
