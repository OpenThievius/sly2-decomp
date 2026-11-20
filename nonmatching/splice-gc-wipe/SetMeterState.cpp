// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetmenu.h"
struct BVT { char pad[0x188]; short delta; short unused; void (*fn)(void *, int); };
struct Blot { char pad[0xC]; BVT *vt; };
struct ITEMDEF { int a; int b; int price; int shown; char pad[16]; };
struct Meter { char pad0[0x20]; float low; char pad1[4]; float high; char pad2[4]; unsigned state; int actor; Blot *blot; int arg3C; int arg40; int arg44; int arg48; int arg4C; };
extern ITEMDEF D_002BCD00[];
extern GADGETMENUENTRY D_002C2DE8[];
extern GADGETMENUENTRY D_002C3028[];
extern GADGETMENUENTRY D_002C3148[];
extern "C" {
int FGadgetAcquired(int);
int FIsBasicDerivedFrom(int, int);
void SeekBlotLabel(float, Blot *, int);
void func_00213928(Blot *, int);
void func_00213B00(Blot *, int);
}
#define CALL(blot, arg) ((blot)->vt->fn((char *)(blot) + (blot)->vt->delta, (arg)))
extern "C" void SetMeterState(Meter *self, unsigned state)
{
    if (self->state == state) return;
    if (self->blot == 0) return;
    if (self->state == 2 || self->state == 6) CALL(self->blot, self->arg3C);
    self->state = state;
    if (state >= 8) return;
    int argument;
    switch (state) {
    case 0:
    case 5:
        argument = self->arg44;
        goto common;
    case 1: {
        int count = 0;
        GADGETMENUENTRY *entries = 0;
        CALL(self->blot, self->arg3C);
        func_00213B00(self->blot, 0x34F);
        SeekBlotLabel(1.0f - self->low, self->blot, 0x34F);
        if (FIsBasicDerivedFrom(self->actor, 0x35)) { count = 0x12; entries = D_002C2DE8; }
        else if (FIsBasicDerivedFrom(self->actor, 0x37)) { count = 9; entries = D_002C3028; }
        else if (FIsBasicDerivedFrom(self->actor, 0x36)) { count = 8; entries = D_002C3148; }
        GADGETMENUENTRY *entry = entries;
        int found = 0;
        for (int index = 0; index < count; index++) {
            int id = entry->id;
            GADGETMENUENTRY *next = entry + 1;
            entry = next;
            if (FGadgetAcquired(id)) {
                ITEMDEF item = D_002BCD00[id];
                if (item.shown > 0) { found = 1; break; }
            }
        }
        if (found) {
            func_00213B00(self->blot, 0x350);
            SeekBlotLabel(1.0f - self->high, self->blot, 0x350);
        } else {
            func_00213928(self->blot, 0x350);
        }
        break;
    }
    case 2:
        argument = self->arg40;
        goto common;
    case 6:
        argument = self->arg48;
    common:
        CALL(self->blot, argument);
        break;
    case 7:
        CALL(self->blot, self->arg4C);
        break;
    }
}
