// SPDX-License-Identifier: GPL-3.0-or-later
#include "alo.h"

extern "C" {
void UpdateAloXfWorld();

void UpdateAloXfWorldHierarchy(ALO *palo)
{
    UpdateAloXfWorld();
    for (LO *plo = (LO *)palo->dlChild.head; plo != palo->ploChildEnd; plo = plo->ploNext) {
        plo->UpdateXfWorldHierarchy();
    }
}
}
