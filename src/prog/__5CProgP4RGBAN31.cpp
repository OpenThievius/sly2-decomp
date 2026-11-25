// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "rgba.h"
extern "C" {
struct CPROG_1C8CC0 {
    int field0; int field4; int field8; int fieldC; char byte10; u8 unknown_0x11[0x50 - 0x11];
    int field50; RGBA color0; RGBA color1; RGBA color2; RGBA color3;
};
CPROG_1C8CC0 *__5CProgP4RGBAN31(CPROG_1C8CC0 *prog, const RGBA *rgba0, const RGBA *rgba1, const RGBA *rgba2, const RGBA *rgba3)
{
    prog->color0 = *rgba0;
    prog->color1 = *rgba1;
    prog->color2 = *rgba2;
    prog->color3 = *rgba3;
    prog->field0 = 0;
    prog->field50 = 0;
    prog->fieldC = 0;
    prog->field8 = 0;
    prog->field4 = 0;
    prog->byte10 = 0;
    return prog;
}
}
