// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"
#include "sw.h"
extern "C" {
void InitSo(GADGETOBJ *);
void InitGadgetObj(GADGETOBJ *gadget) {
    u32 grfSw;
    InitSo(gadget);
    grfSw = gadget->grfSw;
    gadget->field_0x178 = -0xA;
    gadget->field_0x170 = 3000.0f;
    gadget->field_0x158 = -1;
    gadget->state = -1;
    if ((grfSw ^ 1) & 1) {
        gadget->pgrfentry->grf |= 6;
        return;
    }
    gadget->grfSw = grfSw | 6;
}
}
