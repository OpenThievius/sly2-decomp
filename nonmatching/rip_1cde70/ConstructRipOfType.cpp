// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct RIPFIELDS {
    u32 type;
    char pad4[0xE8];
    void *pvt;
};
extern "C" {
void memset(void *, s32, s32);
extern char D_002D7508;
extern char D_002D7558;
extern char D_002D7468;
extern char D_002D7738;
extern char D_002D75F8;
extern char D_002D74B8;
extern char D_002D7648;
extern char D_002D7788;
extern char D_002D7698;
extern char D_002D75A8;
extern char D_002D76E8;
u32 *ConstructRipOfType(RIPFIELDS *self, u32 type, RIPFIELDS *other)
{
    switch (type) {
    case 3:
        memset(self, 0, 0x100);
        self->pvt = &D_002D7738;
        other = self;
        break;
    case 10:
        memset(self, 0, 0x100);
        self->pvt = &D_002D76E8;
        other = self;
        break;
    case 8:
        memset(self, 0, 0x100);
        self->pvt = &D_002D7698;
        other = self;
        break;
    case 6:
        memset(self, 0, 0x110);
        self->pvt = &D_002D7648;
        other = self;
        break;
    case 4:
        memset(self, 0, 0x100);
        self->pvt = &D_002D75F8;
        other = self;
        break;
    case 9:
        memset(self, 0, 0x110);
        self->pvt = &D_002D75A8;
        other = self;
        break;
    case 5:
        memset(self, 0, 0xF0);
        self->pvt = &D_002D74B8;
        other = self;
        break;
    case 1:
        memset(self, 0, 0x100);
        self->pvt = &D_002D7558;
        other = self;
        break;
    case 0:
        memset(self, 0, 0xF0);
        self->pvt = &D_002D7508;
        other = self;
        break;
    case 7:
        memset(self, 0, 0xF0);
        self->pvt = &D_002D7788;
        other = self;
        break;
    case 2:
        memset(self, 0, 0x100);
        self->pvt = &D_002D7468;
        other = self;
        break;
    }
    other->type = type;
    return &other->type;
}
}
