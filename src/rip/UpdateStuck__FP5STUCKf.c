/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"

void UpdateRip__FP3RIPf(struct RIP *rip, float dt);

/* a STUCK (a RIP stuck on an object) updates like any RIP */
void UpdateStuck__FP5STUCKf(struct RIP *stuck, float dt) {
    UpdateRip__FP3RIPf(stuck, dt);
}
