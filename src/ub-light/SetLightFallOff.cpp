// SPDX-License-Identifier: GPL-3.0-or-later
#include "light.h"
struct LIGHTRANGE { float rangeA, rangeB; };
extern "C" void RebuildLight(LIGHT *light);
void SetLightFallOff(LIGHT *light, LIGHTRANGE *range)
{
    *(LIGHTRANGE *)&light->rangeA = *range;
    RebuildLight(light);
}
