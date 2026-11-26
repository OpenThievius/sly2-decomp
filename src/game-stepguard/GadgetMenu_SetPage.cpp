#include "gadgetmenu.h"
#include "blot.h"
#include "clock.h"
#include "swfind.h"
extern "C" void ClearHandsOff(void *, int);
extern "C" void GadgetMenu_RefreshFlags(GADGETMENUOBJ *);
extern "C" void GadgetMenu_SelectGadget(GADGETMENUOBJ *, int);
extern "C" void Menu_SetDialog(GADGETMENUOBJ *, int, int);
extern "C" void SetClockRate(void *, int, float);
extern "C" void SetHandsOff(void *, int);
extern SW B_003DD490;
extern GADGETMENUENTRY D_002C2DE8[];
extern GADGETMENUENTRY D_002C3028[];
extern GADGETMENUENTRY D_002C3148[];
extern const float g_2a79cc;
extern "C" void GadgetMenu_SetPage(GADGETMENUOBJ *self, int page) {
    if (page == self->page) {
        return;
    }
    if (self->page == -1) {
        SetClockRate(&g_2dded0, 0, 0.0f);
        SetHandsOff(&B_003DD490, 0);
        self->Slot10();
    }
    GadgetMenu_SelectGadget(self, -1);
    self->page = page;
    self->clock = g_2dded0.tReal;
    switch (page) {
    case -1: {
        BLOT *object = self->pblot;
        if (object != 0) {
            object->Hide();
        }
        for (int index = 0; index < self->cgme; index++) {
            self->agme[index].labelCur = -1;
        }
        self->cgme = 0;
        self->agme = 0;
        SetClockRate(&g_2dded0, 0, 1.0f);
        ClearHandsOff(&B_003DD490, 0);
        self->Slot11();
        Menu_SetDialog(self, -1, -1);
        self->pblot = 0;
        self->oid = -1;
        break;
    }
    case 0:
        self->oid = 0x375;
        self->cgme = 0x12;
        self->agme = D_002C2DE8;
        break;
    case 1:
        self->oid = 0x376;
        self->cgme = 9;
        self->agme = D_002C3028;
        break;
    case 2:
        self->oid = 0x377;
        self->cgme = 8;
        self->agme = D_002C3148;
        break;
    }
    if (self->page != -1) {
        GadgetMenu_RefreshFlags(self);
        BLOT *found = (BLOT *)PloFindSwObject_thunk(&B_003DD490, 5, self->oid, 0);
        self->pblot = found;
        if (found == 0) {
            GadgetMenu_SetPage(self, -1);
            return;
        }
        found->Select(0x318);
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
