/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ACRC: a constant animation curve (0x12B4F8 loader reads the position, 0x12B590 evaluates it). */
#ifndef SLY2_ACRC_H
#define SLY2_ACRC_H
#include "types.h"

struct ACRC {
    u8 unknown_0x0[4];
    float pos[3];
};
#endif
