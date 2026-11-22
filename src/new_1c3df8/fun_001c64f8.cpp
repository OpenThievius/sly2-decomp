// SPDX-License-Identifier: GPL-3.0-or-later
// 0x1C64F8 SetDprizeGlintOids
#include "dprize.h"

extern "C" void func_001C64F8(DPRIZE *pdprize, int oid0, int oid1, int oid2)
{
    pdprize->aoidploGlint[0].oid = oid0;
    pdprize->aoidploGlint[1].oid = oid1;
    pdprize->aoidploGlint[2].oid = oid2;
}
