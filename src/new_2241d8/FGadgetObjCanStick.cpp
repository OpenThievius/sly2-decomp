// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"

int FGadgetObjCanStick(GADGETOBJ *pgadget) {
    switch (pgadget->gadget) {
    case 4:
        return pgadget->state == 1;
    default:
        return 0;
    case 5:
    case 7:
    case 9:
    case 11:
    case 13:
    case 26:
    case 37:
    case 41:
        return 1;
    }
}
