/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

int sceCdMmode(int mode);
extern s32 g_2bd4c4;

void SetCdMmode__Fv(void) {
    if (g_2bd4c4 == 0x14) {
        sceCdMmode(2);
    }
}
