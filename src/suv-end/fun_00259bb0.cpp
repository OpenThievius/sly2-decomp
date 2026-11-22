// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

/* A vtable slot, 8 bytes: this-adjustment, then the method. */
struct VTSLOT {
    s16 delta;
    s16 index;
    void (*method)(void *);
};
struct VTABLE {
    u8 unknown_0x0[8];
    VTSLOT addref;      /* called by the reference's copy constructor (this function) */
};
struct REFCOUNTED {
    u8 unknown_0x0[0xC];
    VTABLE *vt;
};

extern "C" {
void func_00259BB0(REFCOUNTED **ppref, REFCOUNTED *pobject) {
    if (pobject != 0) {
        VTABLE *vt = pobject->vt;
        vt->addref.method((char *)pobject + vt->addref.delta);
    }
    *ppref = pobject;
}

}
