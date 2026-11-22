/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void RemoveLoHierarchy(struct LIGHT *light);
void func_001A3B38(struct LIGHT *light);

void func_001A34B0(struct LIGHT *light) {
    RemoveLoHierarchy(light);
    func_001A3B38(light);
}
