/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "pzo_hide.h"
struct WRAPRANGE {
    f32 minimum;
    f32 maximum;
};

s32 func_00183498(struct ATTACHCYL *attach, struct WRAPRANGE *range) {
    range->minimum = attach->heightOffset * -3.1415927f;
    range->maximum = attach->heightOffset * 3.1415927f;
    return 1;
}
