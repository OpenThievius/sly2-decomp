/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

s32 func_002064A0(struct STEPGUARDVIEW *guard) {
    s32 value = guard->field_0x33C - 1;
    return ((value <= -1) ? 0 : value) + 1;
}
