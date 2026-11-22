// SPDX-License-Identifier: GPL-3.0-or-later
// 0x12D210 FUN_0012d210
struct LOOKAT_12D210 {
    unsigned char unknown_0x0[0x70];
    int field_0x70;
    int field_0x74;
};

void FUN_0012D210(LOOKAT_12D210 *plookat)
{
    plookat->field_0x70 = 0;
    plookat->field_0x74 = 0;
}
