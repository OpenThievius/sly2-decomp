/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void RebuildLight(struct LIGHT *light);
void RotateXfmToMat(struct LIGHT *light);

void RotateLightToMat(struct LIGHT *light) {
    RotateXfmToMat(light);
    RebuildLight(light);
}
