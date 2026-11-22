// SPDX-License-Identifier: GPL-3.0-or-later
#include "ambview.h"

void AMB_AddRef(struct AMBVIEW *pamb) {
    pamb->cRef = (u16) (pamb->cRef + 1);
}
