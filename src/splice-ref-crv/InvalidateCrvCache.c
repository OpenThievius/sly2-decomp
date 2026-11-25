/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crv.h"

void InvalidateCrvCache(struct CRV *crv) {
    crv->icvHint = 0;
    crv->field_0x148 = -1;
}
