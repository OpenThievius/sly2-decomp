// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "jt.h"
#include "gadgetlist.h"

extern "C" {
extern SW B_003DD490;
PO *PpoSwFocusBase(SW *);
s32 FIsBasicDerivedFrom(BASIC *, s32);
const char *PchzStringFromId(SW *, s32);
char *strcpy(char *, const char *);
}

void func_002111F0(char *dest, int index) {
    JT *focus = (JT *)PpoSwFocusBase(&B_003DD490);
    if (focus == 0 || FIsBasicDerivedFrom(focus, 0x34) == 0)
        return;
    GADGETLIST *gadget = focus->pgadgetlist;
    if (gadget == 0 || index >= gadget->count)
        return;
    strcpy(dest, PchzStringFromId(&B_003DD490, gadget->apentry[index]->stringId));
}
