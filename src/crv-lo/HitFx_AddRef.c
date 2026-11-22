/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "hitfx.h"

void HitFx_AddRef(struct HITFX *pfx)
{
    pfx->cRef = pfx->cRef + 1;
}
