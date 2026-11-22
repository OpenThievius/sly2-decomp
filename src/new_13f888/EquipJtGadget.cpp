// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "jt.h"
struct Slot { int gadget; int state; float t; };
extern "C" {
CRef func_001D8B20(const CRef &value, const char *first, ...);
void SetJtGadgetSlotState(JT *, Slot *, int);
int sprintf(char *, const char *, ...);
extern float g_2dded0[];
extern const char RO_002A4D50[];
extern const char RO_002A4D58[];
}
void EquipJtGadget(JT *jt, unsigned slot, int gadget)
{
    if (slot < 3) {
        Slot *equip = (Slot *)&jt->aslot[slot];
        SetJtGadgetSlotState(jt, equip, -1);
        equip->gadget = gadget;
        equip->state = 0;
        equip->t = g_2dded0[0];
        Slot *scan = (Slot *)jt->aslot;
        Slot *other = (Slot *)jt->aslot;
        for (int index = 0; index < 3; index++, other++) {
            if (index != slot && other->gadget == gadget) {
                SetJtGadgetSlotState(jt, other, -1);
                other->gadget = -1;
            }
            char name[16];
            sprintf(name, RO_002A4D50, index);
            int value = scan->gadget;
            scan++;
            func_001D8B20(CRef(value, TAGK_S32), jt->Slot103(), RO_002A4D58, name, 0);
        }
        jt->Slot105();
    }
}
