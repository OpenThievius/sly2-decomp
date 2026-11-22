/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void PostLoLoad(struct LIGHT *light);
void RebuildLight(struct LIGHT *light);

void PostLightLoad(struct LIGHT *light) {
    PostLoLoad(light);
    RebuildLight(light);
}
