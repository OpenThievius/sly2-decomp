// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"

/* the slot of a gadget among Bentley's six (BENTLEY::aslot, 0xC bytes each) */
extern "C" BENTLEYSLOT *PslotBentleyGadget(BENTLEY *pbentley, s32 gadget)
{
    switch (gadget) {
    case 5:
        return &pbentley->aslot[0];
    case 7:
        return &pbentley->aslot[1];
    case 9:
        return &pbentley->aslot[2];
    case 11:
        return &pbentley->aslot[3];
    case 13:
        return &pbentley->aslot[4];
    case 4:
        return &pbentley->aslot[5];
    default:
        return 0;
    }
}
