/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void LoadXfmFromBrx(void *prtalo, void *pbis);

void RtAlo_LoadFromBrx(void *prtalo, void *pbis) {
    LoadXfmFromBrx(prtalo, pbis);
}
