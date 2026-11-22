/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"

void SetRipgEmitb__FP4RIPGP5EMITB(struct RIPG *ripg, struct EMITB *emitb) {
    ripg->field_0x158 = emitb->params.field_0x14;
}
