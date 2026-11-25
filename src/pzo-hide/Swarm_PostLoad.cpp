// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "alloc.h"
#include "dl.h"

struct SWOBJ;
struct SWPART {
    s32 oid;
    s32 count;
    s32 pad8[2];
    DL dl;
    s32 pad1C[2];
    SWOBJ *object;
    s32 pad28[2];
};
struct SWSLOT {
    s32 id;
    struct SWPART *owner;
    s32 pad8;
    s32 link;
    u64 flags;
    u8 unknown_0x18[0x98];
};
struct SWHOLDER {
    u8 unknown_0x0[0x28];
    u64 flagsHigh;
    u8 unknown_0x30[0x30];
    s32 id;
    u8 unknown_0x64[0x7C];
    s32 slotCount;
    SWSLOT *slots;
    u8 unknown_0xE8[0xE0];
    s32 partCount;
    SWPART parts[1];
};
struct SWENTRY {
    s32 pad[2];
};
extern "C" {
extern s32 B_003DD490[];
s32 PloFindSwObject_thunk(void *, s32, s32, SWHOLDER *);
void InitDl__FP2DLi(DL *, s32);
void AppendDlEntry(DL *, void *);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void func_0017F138(SWHOLDER *);
void AddSoGeomsToOxa(SWHOLDER *);

void Swarm_PostLoad(SWHOLDER *self)
{
    s32 index;
    s32 count;
    for (index = 0; index < self->partCount; index++) {
        SWPART *part = &self->parts[index];
        part->object = (SWOBJ *)PloFindSwObject_thunk(B_003DD490, 4, part->oid, self);
        if (part->object == 0) {
            index--;
            self->partCount = self->partCount - 1;
        } else {
            InitDl__FP2DLi(&part->dl, 0x60);
            for (count = 0; count < part->count; count++) {
                ALLOCREQ request;
                request.cb = 0x70;
                request.cbAlign = 0x10;
                s32 *entry = (s32 *)PvAllocSwClearImpl__Fi(&request);
                entry[8] = (sptr)part;
                entry[9] = -1;
                AppendDlEntry(&part->dl, entry);
            }
        }
    }
    func_0017F138(self);
    SWSLOT *slot = &self->slots[self->slotCount++];
    slot->id = self->id;
    slot->link = -1;
    slot->owner = (SWPART *)self;
    slot->flags |= 0x8000L << 33;
    slot->flags |= 0x8000L << 34;
    if ((int)(self->flagsHigh >> 0x3C) & 1) {
        AddSoGeomsToOxa(self);
    }
}
}
