// SPDX-License-Identifier: GPL-3.0-or-later
#include "joy.h"
/* the menu object (GadgetMenu, ShopMenu and JobMenu share it): 0xC bytes, the vtable pointer, the controller it reads at 0x10 and the
   selected stick direction at 0x28. Slot 14 selects a direction (-1 for none). */
struct MENU_k02_base {
    u8 unknown_0x0[0xC];
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void SelectStick(int index);
};
struct MENU_k02 : MENU_k02_base {
    /* 0x10 */ JOY *pjoy;
    u8 unknown_0x14[0x28 - 0x14];
    /* 0x28 */ int stickIndex;
};
extern "C" float atan2f(float, float);
extern "C" void Menu_UpdateStick(MENU_k02 *pthis)
{
    JOY *psrc = pthis->pjoy;
    if (psrc == 0)
        return;
    int stickIndex = pthis->stickIndex;
    if (stickIndex == -1) {
        if (0.8f < psrc->uStickLeft) {
            float angle = atan2f(psrc->yStick, psrc->xStick);
            float scaled = angle * 1.27323949f + 8.5f;
            int target = (int)scaled;
            int wrapped = (stickIndex < target) ? target : target + 7;
            int remainder = target - ((wrapped >> 3) << 3);
            pthis->SelectStick(remainder);
        }
    } else {
        if (psrc->uStickLeft < 0.5f)
            pthis->SelectStick(-1);
    }
}
