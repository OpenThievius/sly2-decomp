/* SPDX-License-Identifier: GPL-3.0-or-later */
/* HEAPALLOC: the allocator object a hash table (and the movie font's blot) keeps by pointer: its vtable pointer is its first word and
   its virtuals take the size and a flags word (3, 0x1F). Slot 1 allocates (HashTable_Insert, func_00213CD8), slot 2 reallocates
   (HashTable_Resize), slot 3 frees (HashTable_Clear). Slot numbers by the vtable offsets 0x8, 0x10 and 0x18 the retail calls use. */
#ifndef SLY2_HEAPALLOC_H
#define SLY2_HEAPALLOC_H
struct HEAPALLOC {
    virtual void *Alloc(int cb, int flags);                 /* 1: HashTable_Insert, func_00213CD8 */
    virtual void *Realloc(void *pv, int cb, int flags);     /* 2: HashTable_Resize */
    virtual void Free(void *pv);                            /* 3: HashTable_Clear */
};
#endif
