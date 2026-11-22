/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct GEOMENTRY {
    u8 unknown_0x0[4];
    s32 field_0x4;
};
struct GEOMOWNER {
    u8 unknown_0x0[0xE4];
    struct GEOMENTRY *pgeom;
};

s32 func_002589F0(struct GEOMOWNER *owner) {
    return owner->pgeom->field_0x4;
}
