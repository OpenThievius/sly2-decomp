/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct GEOMENTRY {
    u8 unknown_0x0[0x10];
    s32 field_0x10;
};
struct GEOMOWNER {
    u8 unknown_0x0[0xE4];
    struct GEOMENTRY *pgeom;
};

s32 func_00258AB8(struct GEOMOWNER *owner) {
    return owner->pgeom->field_0x10;
}
