/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void bevy_classes_k30_cam_150ef0(struct K30CAM *);

void func_00150E60(struct K30CAM *camera, s32 value) {
    camera->field_0x14 = value;
    if (camera->active != 0) {
        bevy_classes_k30_cam_150ef0(camera);
    }
    camera->active = 0;
}
