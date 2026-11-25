#include "gadgetmenu.h"
struct VT_1DB520 {
    u8 unknown_0x0[0x50]; short delta50; short unused50; void (*fn50)(void *);
    short delta58; short unused58; void (*fn58)(void *);
    u8 unknown_0x60[0x188 - 0x60]; short delta188; short unused188; void (*fn188)(void *, int);
    short delta190; short unused190; void (*fn190)(void *);
};
struct Object_1DB520 { u8 unknown_0x0[0xC]; VT_1DB520 *vt; };
extern "C" void ClearHandsOff(void *, int);
extern "C" void GadgetMenu_RefreshFlags(GADGETMENU *);
extern "C" void GadgetMenu_SelectGadget(GADGETMENU *, int);
extern "C" void Menu_SetDialog(GADGETMENU *, int, int);
extern "C" Object_1DB520 *PloFindSwObject_thunk(void *, int, int, int);
extern "C" void SetClockRate(void *, int, float);
extern "C" void SetHandsOff(void *, int);
extern char B_003DD490[];
extern GADGETMENUENTRY D_002C2DE8[];
extern GADGETMENUENTRY D_002C3028[];
extern GADGETMENUENTRY D_002C3148[];
struct Clock_1DB520 { u8 unknown_0x0[0x3C]; float rate; };
extern Clock_1DB520 g_2dded0;
extern const float g_2a79cc;
extern "C" void GadgetMenu_SetPage(GADGETMENU *self, int page) {
    if (page == self->page) {
        return;
    }
    if (self->page == -1) {
        SetClockRate(&g_2dded0, 0, 0.0f);
        SetHandsOff(B_003DD490, 0);
        ((VT_1DB520 *)self->vtable)->fn50((char *)self + ((VT_1DB520 *)self->vtable)->delta50);
    }
    GadgetMenu_SelectGadget(self, -1);
    self->page = page;
    self->clock = g_2dded0.rate;
    switch (page) {
    case -1: {
        Object_1DB520 *object = (Object_1DB520 *)self->pblot;
        if (object != 0) {
            object->vt->fn190((char *)object + object->vt->delta190);
        }
        for (int index = 0; index < self->cgme; index++) {
            self->agme[index].labelCur = -1;
        }
        self->cgme = 0;
        self->agme = 0;
        SetClockRate(&g_2dded0, 0, 1.0f);
        ClearHandsOff(B_003DD490, 0);
        ((VT_1DB520 *)self->vtable)->fn58((char *)self + ((VT_1DB520 *)self->vtable)->delta58);
        Menu_SetDialog(self, -1, -1);
        self->pblot = 0;
        self->idDialog = -1;
        break;
    }
    case 0:
        self->idDialog = 0x375;
        self->cgme = 0x12;
        self->agme = D_002C2DE8;
        break;
    case 1:
        self->idDialog = 0x376;
        self->cgme = 9;
        self->agme = D_002C3028;
        break;
    case 2:
        self->idDialog = 0x377;
        self->cgme = 8;
        self->agme = D_002C3148;
        break;
    }
    if (self->page != -1) {
        GadgetMenu_RefreshFlags(self);
        Object_1DB520 *found = PloFindSwObject_thunk(B_003DD490, 5, self->idDialog, 0);
        self->pblot = (sptr)found;
        if (found == 0) {
            GadgetMenu_SetPage(self, -1);
            return;
        }
        found->vt->fn188((char *)found + found->vt->delta188, 0x318);
        float best = g_2a79cc;
        int bestId = -1;
        if (self->cgme > 0) {
            GADGETMENUENTRY *entry = self->agme;
            int remaining = self->cgme;
            do {
                remaining -= 1;
                if (entry->flags & 4) {
                    float sum = entry->low + entry->high;
                    if (sum < best) {
                        bestId = entry->id;
                        best = sum;
                    }
                }
                entry += 1;
            } while (remaining != 0);
        }
        GadgetMenu_SelectGadget(self, bestId);
    }
}
