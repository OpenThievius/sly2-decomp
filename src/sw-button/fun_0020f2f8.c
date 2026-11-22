/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

void UpdateSwFog(struct SWVIEW *psw);

void func_0020F2F8(struct SWVIEW *psw, f32 scale) {
    psw->scaleFog = scale;
    UpdateSwFog(psw);
}
