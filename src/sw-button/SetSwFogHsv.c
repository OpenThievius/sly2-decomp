/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

void UpdateSwFog(struct SWVIEW *psw);

void SetSwFogHsv(struct SWVIEW *psw, QW hsv) {
    psw->hsvFog = hsv;
    UpdateSwFog(psw);
}
