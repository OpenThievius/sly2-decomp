/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void RebuildLight(struct LIGHT *light);
void TranslateXfmToPos(struct LIGHT *light);

void TranslateLightToPos(struct LIGHT *light) {
    TranslateXfmToPos(light);
    RebuildLight(light);
}
