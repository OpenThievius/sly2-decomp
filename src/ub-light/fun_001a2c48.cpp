// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
extern "C" {
struct INTPAIR { s32 first; s32 second; };

extern u32 B_002E1E58;
extern INTPAIR D_002BFBD0[];

void func_001A2C48(s32 *pfirst, s32 *psecond) {
    INTPAIR *pentry;

    if (B_002E1E58 >= 7U) {
        B_002E1E58 = 0;
    }
    pentry = &D_002BFBD0[B_002E1E58];
    if (pfirst != 0) {
        *pfirst = pentry->first;
    }
    if (psecond != 0) {
        *psecond = pentry->second;
    }
}

}
