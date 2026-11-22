// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "sly2.h"
void SetBentleyState(BENTLEY *, int);
void func_001367D8(BENTLEY *pbentley)
{
    int start, now;
    do {
        start = pbentley->field_0x1800;
        if (start != 0) { if (start == 1 && pbentley->psoSurface != 0) {
            SetBentleyState(pbentley, 0);
            pbentley->SetPlayable(1);
        } }
        now = pbentley->field_0x1800;
    } while (now != start && now != -1);
}
