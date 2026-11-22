// SPDX-License-Identifier: GPL-3.0-or-later
#include "light.h"
extern "C" {
void RebuildLight(LIGHT *light);
void func_001A3B38(LIGHT *light);

void SetLightKind(LIGHT *light, s32 mode)
{
    func_001A3B38(light);
    light->mode = mode;
    RebuildLight(light);
}
}
