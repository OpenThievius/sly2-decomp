// SPDX-License-Identifier: GPL-3.0-or-later
#include "light.h"
extern "C" {
void func_001A3B38(LIGHT *light);

void SetLightFExcludeDynamicObjects(LIGHT *light, s32 fExclude) {
    if (fExclude != light->fExcludeDynamicObjects) {
        func_001A3B38(light);
        light->fExcludeDynamicObjects = fExclude;
        if (fExclude != 0) {
            light->fDynamic = 0;
        }
        func_001A3B38(light);
    }
}
}
