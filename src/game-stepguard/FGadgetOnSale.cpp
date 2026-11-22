// SPDX-License-Identifier: GPL-3.0-or-later
#include "shopmenu.h"
extern "C" {
int NEpisodeBest(void);
extern GADGETDEF D_002BCD00[];

int FGadgetOnSale(int index) {
    GADGETDEF *gadget = &D_002BCD00[index];
    if (gadget->episodeMin == -1) {
        return 0;
    }
    return NEpisodeBest() >= gadget->episodeMin;
}
}
