/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void *InitCplcy(void *);
extern char D_002CD4E0[];

struct CPLOOK *InitCplook(struct CPLOOK *look) {
    InitCplcy(look);
    look->vtable = D_002CD4E0;
    look->field_0x28 = 7.0f;
    look->ambience = 0;
    look->field_0x38 = 0;
    return look;
}
