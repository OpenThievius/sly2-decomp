#include "types.h"
struct Entry { Entry *next; int unk0x4; };
struct Sw { u8 unknown_0x0[0x40]; Entry *freeList; };
struct Owner { u8 unknown_0x0[0x3F18]; int freeCount; };
void RemoveSwGrfEntry(Owner *owner, Sw *sw)
{
    Entry *entry = sw->freeList;
    if (((sptr)entry ^ 1) & 1) {
        sw->freeList = entry->next;
        entry->next = 0;
        entry->unk0x4 = 0;
        owner->freeCount = owner->freeCount + 1;
    }
}
