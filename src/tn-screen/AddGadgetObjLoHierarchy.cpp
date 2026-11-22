// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"
extern "C" {
void AddSoLoHierarchy(GADGETOBJ *);
void func_001F1448(SM *, GADGETOBJ *, s32, s32, SMA **);
/* 0x224028: add the hierarchy, then if the state machine at +0x164 is set, apply it with the animation reference at +0x168 */
void AddGadgetObjLoHierarchy(GADGETOBJ *gadget) {
    SM *psm;
    AddSoLoHierarchy(gadget);
    psm = gadget->psm;
    if (psm != 0) {
        func_001F1448(psm, gadget, -1, 0, &gadget->psma);
    }
}
}
