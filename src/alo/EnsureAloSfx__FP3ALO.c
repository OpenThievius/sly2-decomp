/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "alo.h"

void func_001CC2E8(struct ALOSFX *);

void EnsureAloSfx__FP3ALO(struct ALO *palo) {
    if (palo->sfx.field_0x108 == 0) {
        func_001CC2E8(&palo->sfx);
    }
}
