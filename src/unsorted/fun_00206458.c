/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

s32 func_00206458(struct STEPGUARDVIEW *guard) {
    s32 value = guard->field_0x338 - 1;
    return (s32) ((value <= -1) ? 0 : value) / 10;
}
