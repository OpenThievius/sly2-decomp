/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "joy.h"

void SetVjoyMode(struct JOY *pjoy, s32 vjoym) {
    pjoy->vjoym = vjoym;
    if (vjoym == 1) {
        pjoy->field_0x78 = 0xFFFF;
    }
}
