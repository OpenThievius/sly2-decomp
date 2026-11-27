#include "sw.h"
struct Entry { Entry *next; int unk0x4; };
struct Sw { u8 unknown_0x0[0x40]; Entry *freeList; };
void RemoveSwGrfEntry(SW *psw, Sw *sw)
{
    Entry *entry = sw->freeList;
    if (((sptr)entry ^ 1) & 1) {
        sw->freeList = entry->next;
        entry->next = 0;
        entry->unk0x4 = 0;
        psw->cgrfentryDead = psw->cgrfentryDead + 1;
    }
}
