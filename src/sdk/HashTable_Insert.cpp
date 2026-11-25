#include "heapalloc.h"
#include "sly2.h"
struct HashEntry { int hash; int key; int value; int next; };
struct HashTable { unsigned buckets; HashEntry **table; int count; HEAPALLOC *alloc; };
extern "C" {
void HashTable_Resize(HashTable *, int);
int HashSz(int);
int *HashTable_Insert(HashTable *table, int *key, int *value)
{
    table->count++;
    if (!table->buckets) HashTable_Resize(table, 0x35);
    unsigned hash = HashSz(*key);
    unsigned bucket = hash % table->buckets;
    HEAPALLOC *alloc = table->alloc;
    HashEntry *entry = (HashEntry *)alloc->Alloc(0x10, 3);
    memset(entry, 0, 0x10);
    entry->hash = hash;
    entry->key = *key;
    entry->value = *value;
    entry->next = (sptr)table->table[bucket];
    table->table[bucket] = entry;
    return &entry->value;
}
}
