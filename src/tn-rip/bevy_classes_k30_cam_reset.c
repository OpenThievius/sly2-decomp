/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void VirtualRefPtr_Assign(void **, void *);

void bevy_classes_k30_cam_reset(struct K30CAM *camera) {
    VirtualRefPtr_Assign(&camera->field_0xC4, 0);
    VirtualRefPtr_Assign(&camera->field_0xC0, 0);
}
