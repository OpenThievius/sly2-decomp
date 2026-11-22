/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void bevy_classes_k30_cam_150ef0(struct K30CAM *);

void bevy_classes_k30_cam_set(struct K30CAM *camera, s32 target) {
    camera->field_0x10 = target;
    if (camera->active != 0) {
        bevy_classes_k30_cam_150ef0(camera);
    }
    camera->active = 0;
}
