/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

s32 FSwHandsOff(struct SWVIEW *psw) {
    return psw->chandsOff > 0;
}
