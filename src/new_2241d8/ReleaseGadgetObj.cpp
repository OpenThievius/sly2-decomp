// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"

void ReleaseGadgetObj(GADGETOBJ *pgadget)
{
    if (pgadget->gadget == 0xB) {
        pgadget->SetState(5);
        return;
    }
    pgadget->SetState(3);
}
