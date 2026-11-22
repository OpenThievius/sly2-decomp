// SPDX-License-Identifier: GPL-3.0-or-later
// 0x1C4080 GetPoVjoyMode
#include "joy.h"
#include "po.h"

extern "C" int GetPoVjoyMode(PO *ppo)
{
    JOY *pjoy = ppo->pjoy;
    int vjoym = -1;
    if (pjoy != 0)
        vjoym = pjoy->vjoym;
    return vjoym;
}
