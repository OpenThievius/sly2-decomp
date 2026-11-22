// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
extern "C" int FCheckJtCaneSide(JT *);
extern "C" int ChooseJtCaneAlternateSwing(SLY *jt)
{
    int next;
    switch (jt->jtcs) {
    case 0x16: next = 0x17; break;
    case 0x17: next = 0x16; break;
    default: next = FCheckJtCaneSide(jt) ? 0x17 : 0x16; break;
    }
    return next;
}
