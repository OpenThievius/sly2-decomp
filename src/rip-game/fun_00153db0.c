/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "guard.h"

void UpdateLo(struct LO *plo);
void func_00153DE0(struct SENSOR *psensor);

void func_00153DB0(struct SENSOR *sensor) {
    UpdateLo((struct LO *)sensor);
    func_00153DE0(sensor);
}
