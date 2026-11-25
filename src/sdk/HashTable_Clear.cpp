#include "heapalloc.h"
#include "sly2.h"
struct ENTRY { u8 unknown_0x0[0xC]; ENTRY *next; };
struct HASHTABLE { int cBucket; ENTRY **pab; int c; HEAPALLOC *palloc; };

extern "C" void HashTable_Clear(HASHTABLE *pht)
{
    for (int ibucket = 0; ibucket < pht->cBucket; ibucket++) {
        ENTRY *pentry = pht->pab[ibucket];
        while (pentry != 0) {
            ENTRY *pentryNext = pentry->next;
            pht->palloc->Free(pentry);
            pentry = pentryNext;
        }
    }
    memset(pht->pab, 0, pht->cBucket << 2);
    pht->c = 0;
    pht->palloc->Free(pht->pab);
    pht->cBucket = 0;
    pht->pab = 0;
}
