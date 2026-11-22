/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

struct DCB *PdcbAllocSw(struct SWVIEW *psw) {
    s32 idcb;

    idcb = psw->cdcb;
    psw->cdcb = idcb + 1;
    return psw->adcb + idcb;
}
