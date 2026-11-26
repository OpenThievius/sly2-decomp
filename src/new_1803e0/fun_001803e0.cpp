// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"

/* two 0x40-byte entries, each with a target object at 0xC, then a float at 0x98 */
struct TARGETENTRY {
    u8 unknown_0x0[0xC];
    s32 target;
    u8 unknown_0x10[0x30];
};

struct TARGETPAIR {
    TARGETENTRY entry[2];
    u8 unknown_0x80[0x18];
    float one;
};

/* a SOHIT subclass (its own fields start at 0x1C0; func_0017F5B0, SOHIT's SoHit_QueueTouch, takes it); class unnamed */
struct Holder : SOHIT {
    u8 unknown_0x1C0[0xC];
    /* 0x1CC */ s32 flag; /* reader: func_001803E0 */
};

extern "C" {
s32 FIsBasicDerivedFrom(s32, s32);
void func_0017F1A0(Holder *, TARGETPAIR *, s32);
void func_0017F5B0(SOHIT *, void *);
}

extern "C" void func_001803E0(Holder *holder, TARGETPAIR *pair, s32 index)
{
    func_0017F1A0(holder, pair, index);
    s32 target = pair->entry[1 - index].target;
    if (FIsBasicDerivedFrom(target, 0x47) == 0 && holder->flag != 0) {
        goto setOne;
    }
    func_0017F5B0(holder, (void *)target);
    if (holder->flag == 0) {
        return;
    }
setOne:
    pair->one = 1.0f;
}
