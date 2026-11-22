/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void ReleaseJtLookHold(struct JTVIEW *pjt) {
    pjt->fLookHold = 0;
}
