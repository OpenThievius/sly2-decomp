// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"

/* the rope simulation PattachCrv builds (ConstructRopeSim); only the mode is read here */
struct ROPESIM {
    u8 unknown_0x0[0x4C];
    /* 0x4C */ s32 mode; /* func_001E6340: 0 and 3 update it as a free rope, 1 and 2 as a chain */
};

extern "C" void UpdateRopeSimChain(ROPESIM *, CRV *);
extern "C" void UpdateRopeSimFree(ROPESIM *, CRV *);
extern "C" void func_001A5E80(LO *);
extern "C" void func_001E6340(CRV *self)
{
    ROPESIM *rope = self->pattach;
    if (rope != 0) {
        s32 mode = rope->mode;
        switch (mode) {
        case 0: case 3: UpdateRopeSimFree(self->pattach, self); break;
        case 1: case 2: UpdateRopeSimChain(rope, self); break;
        }
    } else {
        func_001A5E80(self);
    }
}
