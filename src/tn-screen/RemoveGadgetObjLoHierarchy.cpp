// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"

extern "C" void RemoveSoLoHierarchy(GADGETOBJ *);
extern "C" void RetractSmaRef(SMA **);

void RemoveGadgetObjLoHierarchy(GADGETOBJ *gadget)
{
    RemoveSoLoHierarchy(gadget);
    gadget->SetState(-1);
    RetractSmaRef(&gadget->psma);
}
