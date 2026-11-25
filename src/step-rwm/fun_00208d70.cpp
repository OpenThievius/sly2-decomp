// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" u64 GrfsgsFromSgs(int);
extern "C" int func_00208D70(STEPGUARD *pguard)
{
    u64 blind = GrfsgsFromSgs(0xB) | GrfsgsFromSgs(0x1D) | GrfsgsFromSgs(7) |
                          GrfsgsFromSgs(5) | GrfsgsFromSgs(6) | GrfsgsFromSgs(0x10) |
                          GrfsgsFromSgs(1) | GrfsgsFromSgs(0x16) | GrfsgsFromSgs(0x2A);
    if ((blind & pguard->grfsgs) != 0)
        return 0;
    return pguard->sensing;
}
