// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
extern "C" {
u64 GrfsgsFromSgs(s32);

s32 AsgsFromGrfsgs(u64 grfsgs, s32 *asgs) {
    s32 *pasgs;
    s32 sgs;
    s32 csgs;

    sgs = 0x2E;
    pasgs = asgs;
    csgs = 0;
    do {
        if (grfsgs & GrfsgsFromSgs(sgs)) {
            *pasgs = sgs;
            csgs += 1;
            pasgs += 1;
        }
        sgs -= 1;
    } while (sgs >= 0);
    return csgs;
}

}
