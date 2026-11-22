// SPDX-License-Identifier: GPL-3.0-or-later
#include "light.h"
extern "C" {
void func_001A3B38(LIGHT *light);

void SetLightDynamic(LIGHT *light, s32 fDynamic) {
    if (fDynamic != light->fDynamic) {
        func_001A3B38(light);
        light->fDynamic = fDynamic;
        if (fDynamic != 0) {
            light->fExcludeDynamicObjects = 0;
        }
        func_001A3B38(light);
    }
}
}
