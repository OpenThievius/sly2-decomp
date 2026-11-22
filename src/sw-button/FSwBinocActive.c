/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

s32 FSwBinocActive(struct SWVIEW *psw) {
    return psw->cbinoc > 0;
}
