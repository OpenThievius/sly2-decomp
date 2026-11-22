// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
extern "C" void SetSwFocusOverride(SW *, int);
void func_002102A0(SW *psw)
{
    SetSwFocusOverride(psw, 0);
    for (int cid = 0; cid <= 0xC6; cid++) {
        /* the byte offset keeps retail's invariant base (psw itself) in a register: aslCid[cid] folds 0x3038 into it (3 words off) */
        SL *psl = (SL *)((char *)psw->aslCid + cid * 12);
        LO *plo = (LO *)psl->pvFirst;
        while (plo != 0) {
            plo->Slot24();
            plo = plo->ploNextCid;
        }
    }
}
