// SPDX-License-Identifier: GPL-3.0-or-later
#include "cplcy.h"
extern "C" {
void DeactivateCplcy();
s32 SetResetFlag__FP2CM(struct CM *);
extern struct CM B_002DDF40;

void bevy_camera_policy_deactivate(struct CPPOLICY *policy, s32 unused, struct CPSOURCE *source) {
    DeactivateCplcy();
    if (source->field_0xC != 0) {
        SetResetFlag__FP2CM(&B_002DDF40);
    }
    struct CPOBJECT *object = policy->holder->object;
    struct CPVTABLE *vtable = object->vtable;
    vtable->fn_0x14((char *)object + vtable->delta_0x10);
    policy->holder = 0;
}

}
