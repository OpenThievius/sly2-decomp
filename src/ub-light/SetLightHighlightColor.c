/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void RebuildLight(struct LIGHT *light);

void SetLightHighlightColor(struct LIGHT *light, QW hsv) {
    *(QW *)&light->hsv = hsv;
    RebuildLight(light);
}
