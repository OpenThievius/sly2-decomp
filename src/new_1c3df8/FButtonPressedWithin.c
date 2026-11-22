/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "joy.h"

void ClearVjoyPresses(struct JOY *pjoy, s32 grfbtn); /* extern */
s32 GrfbtnVjoyPressedWithin(struct JOY *pjoy, u32 grfbtn, f32 dt); /* extern */

s32 FButtonPressedWithin(struct JOY *pjoy, u32 grfbtn, f32 dt) {
    s32 grfbtnPressed;

    grfbtnPressed = GrfbtnVjoyPressedWithin(pjoy, grfbtn, dt);
    ClearVjoyPresses(pjoy, grfbtnPressed);
    return grfbtnPressed;
}
