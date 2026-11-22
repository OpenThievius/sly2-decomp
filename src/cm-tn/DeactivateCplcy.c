/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void SetCmNearClip(struct CM *, f32);
extern struct CM B_002DDF40;

void DeactivateCplcy(struct CPLCY *policy) {
    policy->active = 0;
    SetCmNearClip(&B_002DDF40, policy->savedNearClip);
    B_002DDF40.field_0x24 = (f32) policy->savedField_0x24;
}
