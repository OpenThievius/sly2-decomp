// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
extern "C" void PloCloneLo(LO *, SO *);

void CloneAloHierarchy(SO *palo, SO *base)
{
    palo->Slot41(base);
    LO *lo = (LO *)base->dlChild.head;
    if (lo != base->ploChildEnd) {
        do {
            if ((lo->grfo & (1UL << 57)) == 0)
                PloCloneLo(lo, palo);
            lo = lo->ploNext;
        } while (lo != base->ploChildEnd);
    }
}
