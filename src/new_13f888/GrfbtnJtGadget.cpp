// SPDX-License-Identifier: GPL-3.0-or-later
#include "jt.h"
extern "C" {
extern unsigned D_002C3258[];
}

/* the buttons of the player's gadget slots (JT::aslot) that hold gadget nKey */
extern "C" unsigned GrfbtnJtGadget(JT *pjt, int nKey)
{
    GADGETSLOT *pslot = pjt->aslot;
    unsigned *pFlags = D_002C3258;
    unsigned accumulated = 0;
    int nRemain = 2;
    do {
        if (nKey == pslot->gadget) {
            accumulated |= *pFlags;
        }
        pFlags++;
        pslot++;
        nRemain--;
    } while (nRemain >= 0);
    return accumulated;
}
