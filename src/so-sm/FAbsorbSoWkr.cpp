// SPDX-License-Identifier: GPL-3.0-or-later
// 0x1F7588 FAbsorbSoWkr
#include "so.h"
#include "wkr.h"
int FAbsorbSoWkr(SO *, WKR *wkr)
{
    return wkr->flags != 0;
}
