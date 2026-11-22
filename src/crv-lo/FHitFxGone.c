/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "dl.h"

s32 FFindDlEntry(struct DL *pdl, void *pv);
extern struct DL B_003E148C;

s32 FHitFxGone(void *pfx)
{
    return FFindDlEntry(&B_003E148C, pfx) == 0;
}
