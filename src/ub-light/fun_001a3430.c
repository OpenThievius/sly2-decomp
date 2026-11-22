/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void AddLoHierarchy(struct LIGHT *light);
void RebuildLight(struct LIGHT *light);

void func_001A3430(struct LIGHT *light) {
    AddLoHierarchy(light);
    RebuildLight(light);
}
