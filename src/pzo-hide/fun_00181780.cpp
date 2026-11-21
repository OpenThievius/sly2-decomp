/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "lo.h"

struct RSMG;

extern "C" {
void TriggerRsmg(void *, int, void *, void *, int);
extern int B_003DD490;
}

/* A subclass of LO with its rule state machines at 0x200, as the alarm button keeps them (crsmg, arsmg). */
struct RSMGLO : LO {
    u8 unknown_0x50[0x200 - 0x50];
    /* 0x200 */ int crsmg;            /* func_00181780 */
    /* 0x204 */ struct RSMG *arsmg[1]; /* func_00181780 passes its address */
};

extern "C" void func_00181780(RSMGLO *plo)
{
    TriggerRsmg(&B_003DD490, plo->crsmg, plo->arsmg, plo, 1);
    plo->HandleSpliceEvent(5, 0, 0, 0, 0);
}
