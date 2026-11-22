/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "gadgetobj.h"

s32 FGadgetObjIsKindB(struct GADGETOBJ *pgadget) {
    return pgadget->gadget == 0xB;
}
