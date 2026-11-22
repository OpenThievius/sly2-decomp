// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
/* the second argument's class is not known: the function stores one constant at 0x94 of it */
struct OBJ_1374E0 { u8 unknown_0x0[0x94]; f32 field_0x94; };
extern float D_FLT_002BC9B4;
void func_001374E0(void *arg1, OBJ_1374E0 *pobj)
{
    float f = D_FLT_002BC9B4;
    pobj->field_0x94 = f;
}
