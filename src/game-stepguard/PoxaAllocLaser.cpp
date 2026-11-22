// SPDX-License-Identifier: GPL-3.0-or-later
#include "oxa.h"
extern "C" OXA *PoxaAllocSo(void);
extern "C" OXA *PoxaAllocLaser(void)
{
    OXA *poxa = PoxaAllocSo();
    poxa->grf |= 0x20;
    return poxa;
}
