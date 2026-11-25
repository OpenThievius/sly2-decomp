// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetmenu.h"
#include "blot.h"
struct ITEMDEF { int a; int b; int price; int shown; u8 unknown_0x10[16]; };
struct Meter { u8 unknown_0x0[0x20]; float low; u8 unknown_0x24[4]; float high; u8 unknown_0x2C[4]; unsigned state; int actor; BLOT *blot; int arg3C; int arg40; int arg44; int arg48; int arg4C; };
extern ITEMDEF D_002BCD00[];
extern GADGETMENUENTRY D_002C2DE8[];
extern GADGETMENUENTRY D_002C3028[];
extern GADGETMENUENTRY D_002C3148[];
extern "C" {
int FGadgetAcquired(int);
int FIsBasicDerivedFrom(int, int);
void SeekBlotLabel(float, BLOT *, int);
void func_00213928(BLOT *, int);
void func_00213B00(BLOT *, int);
}
extern "C" void SetMeterState(Meter *self, unsigned state)
{
    if (self->state == state) return;
    if (self->blot == 0) return;
    if (self->state == 2 || self->state == 6) self->blot->Select(self->arg3C);
    self->state = state;
    if (state >= 8) return;
    switch (state) {
    case 0:
    case 5:
        self->blot->Select(self->arg44);
        break;
    case 1: {
        int count = 0;
        GADGETMENUENTRY *entries = 0;
        self->blot->Select(self->arg3C);
        func_00213B00(self->blot, 0x34F);
        SeekBlotLabel(1.0f - self->low, self->blot, 0x34F);
        if (FIsBasicDerivedFrom(self->actor, 0x35)) { count = 0x12; entries = D_002C2DE8; }
        else if (FIsBasicDerivedFrom(self->actor, 0x37)) { count = 9; entries = D_002C3028; }
        else if (FIsBasicDerivedFrom(self->actor, 0x36)) { count = 8; entries = D_002C3148; }
        GADGETMENUENTRY *entry = entries;
        int found = 0;
        for (int index = 0; index < count; entry++, index++) {
            int id = entry->id;
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
        self->blot->Select(self->arg40);
        break;
    case 6:
        self->blot->Select(self->arg48);
        break;
    case 7:
        self->blot->Select(self->arg4C);
        break;
    }
}
