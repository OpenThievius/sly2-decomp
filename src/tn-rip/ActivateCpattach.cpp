// SPDX-License-Identifier: GPL-3.0-or-later
#include "cplcy.h"
extern "C" {

void ActivateCplcy();
void SetCmNearClip(struct CM *, f32);
extern struct CM B_002DDF40;

void ActivateCpattach(s32 unused, struct CPATTACHSOURCE *source) {
    ActivateCplcy();
    SetCmNearClip(&B_002DDF40, 49.0f);
    B_002DDF40.radFovTarget = source->field_0x1BC;
}
}
