/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "joy.h"

s32 FVjoyButtonHeld(struct JOY *pjoy, u32 grfbtn) {
    return (pjoy->grfbtn & grfbtn) != 0;
}
