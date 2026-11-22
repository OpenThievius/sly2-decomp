/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void bevy_classes_k30_cam_150ef0(struct K30CAM *);

void func_00150EA0(struct K30CAM *camera, s128 position, s128 target, f32 distance) {
    camera->currentPosition = position;
    camera->currentTarget = target;
    camera->currentDistance = distance;
    if (camera->active == 0) {
        bevy_classes_k30_cam_150ef0(camera);
    }
    camera->active = 1;
}
