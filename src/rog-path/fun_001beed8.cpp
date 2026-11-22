// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "jt.h"
/* the player's focus base, seen as a JT past its first 0xF40 bytes (JT has no member there yet: one reader) */
struct JTREDIRECT { u8 unknown_0x0[0xF40]; void *field_0xF40; };
extern "C" {
extern SW B_003DD490;
PO *PpoSwFocusBase(SW *);
int FIsBasicDerivedFrom(void *, int);
void *PloFindSwObject_thunk(SW *, int, int, void *);
}

static inline void *Redirect(PO *focus)
{
    if (focus != 0) {
        if (FIsBasicDerivedFrom(focus, 0x34) != 0)
            return ((JTREDIRECT *)focus)->field_0xF40;
    }
    return focus;
}

void func_001BEED8(int oid)
{
    switch (oid) {
    case 0x2AE: {
        PO *focus = PpoSwFocusBase(&B_003DD490);
        void *target = Redirect(focus);
        PloFindSwObject_thunk(&B_003DD490, 1, oid, target);
        break;
    }
    case 0x2AF:
        PloFindSwObject_thunk(&B_003DD490, 1, 0x2AF, PpoSwFocusBase(&B_003DD490));
        break;
    default:
        PloFindSwObject_thunk(&B_003DD490, 0x405, oid, 0);
    }
}
