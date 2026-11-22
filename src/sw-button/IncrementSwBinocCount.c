/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

void IncrementSwBinocCount(struct SWVIEW *psw) {
    psw->cbinoc = psw->cbinoc + 1;
}
