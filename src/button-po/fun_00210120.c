/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

struct OPTSET *func_00210120(struct SWVIEW *psw) {
    s32 ioptset;

    ioptset = psw->coptset;
    psw->coptset = ioptset + 1;
    return psw->aoptset + ioptset;
}
