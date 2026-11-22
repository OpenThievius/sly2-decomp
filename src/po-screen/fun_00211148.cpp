// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "jt.h"

#include "gadgetlist.h"
extern "C" {
extern SW B_003DD490;
PO *PpoSwFocusBase(SW *);
s32 FIsBasicDerivedFrom(BASIC *, s32);
char *func_002026F8(GADGETLIST *);
char *func_00202730(GADGETLIST *);
char *strcpy(char *, const char *);
}

void func_00211148(char *dest, int n) {
    JT *focus = (JT *)PpoSwFocusBase(&B_003DD490);
    if (focus == 0 || FIsBasicDerivedFrom(focus, 0x34) == 0)
        return;
    const char *name = 0;
    GADGETLIST *gadget = focus->pgadgetlist;
    if (gadget != 0) {
        if (n != 0) {
            if (n == 1)
                name = func_002026F8(gadget);
        } else
            name = func_00202730(gadget);
    }
    if (name != 0)
        strcpy(dest, name);
}
