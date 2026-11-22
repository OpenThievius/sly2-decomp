/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void *InitCplcy(void *);
extern char D_002CD498[];

struct K30CAM *func_00150728(struct K30CAM *camera) {
    InitCplcy(camera);
    camera->vtable = D_002CD498;
    camera->field_0xB4 = 7.0f;
    camera->minDistance = -1.0f;
    camera->field_0xC0 = 0;
    camera->field_0xC4 = 0;
    return camera;
}
