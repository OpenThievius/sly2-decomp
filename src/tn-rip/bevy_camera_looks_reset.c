/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void VirtualRefPtr_Assign(void **, void *);

void bevy_camera_looks_reset(struct CPLOOK *look) {
    VirtualRefPtr_Assign(&look->field_0x38, 0);
    VirtualRefPtr_Assign(&look->ambience, 0);
}
