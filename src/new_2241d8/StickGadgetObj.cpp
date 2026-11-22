// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"

extern "C" void func_001A58D0(LO *plo, LO *ploParent, int grf);

void StickGadgetObj(GADGETOBJ *pgadget, LO *plo)
{
    int gadget = pgadget->gadget;
    if (gadget == 0x1A || gadget == 0x29) {
        pgadget->SetState(3);
        return;
    }
    if (plo->oid == 1)
        plo = 0;
    func_001A58D0(pgadget, plo, 3);
    pgadget->SetState(2);
}
