/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void UpdateGrfjoytFromGrfusr__Fv(void);
extern s32 B_002DFBC4;

void AddGrfusr__Fi(s32 grfusr) {
    B_002DFBC4 |= grfusr;
    UpdateGrfjoytFromGrfusr__Fv();
}
