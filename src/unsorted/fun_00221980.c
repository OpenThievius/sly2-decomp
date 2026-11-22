/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct FOCUS {
    u8 unknown_0x0[0x70];
    f32 ratio;
};
struct FOCUSOWNER {
    u8 unknown_0x0[0x118];
    struct FOCUS *pfocus;
};

f32 func_00221980(struct FOCUSOWNER *owner) {
    return owner->pfocus->ratio;
}
