/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

void UpdateSwFog(struct SWVIEW *psw);

void func_0020F2D8(struct SWVIEW *psw, f32 alpha) {
    psw->alphaFog = alpha;
    UpdateSwFog(psw);
}
