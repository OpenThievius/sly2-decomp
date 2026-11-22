/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* The stream object CBinaryInputStream_Constructor zeroes (0x34 bytes): twelve zeroed words, its vtable at 0x30. */
struct BINARYINPUTSTREAM {
    s32 field_0x0;
    s32 field_0x4;
    s32 field_0x8;
    s32 field_0xC;
    s32 field_0x10;
    s32 field_0x14;
    s32 field_0x18;
    s32 field_0x1C;
    s32 field_0x20;
    s32 field_0x24;
    s32 field_0x28;
    s32 field_0x2C;
    void *pvtable;
};

extern void *D_002CA5C0[];

struct BINARYINPUTSTREAM *CBinaryInputStream_Constructor(struct BINARYINPUTSTREAM *pbis) {
    pbis->field_0x0 = 0;
    pbis->pvtable = D_002CA5C0;
    pbis->field_0x10 = 0;
    pbis->field_0x4 = 0;
    pbis->field_0x14 = 0;
    pbis->field_0x8 = 0;
    pbis->field_0x18 = 0;
    pbis->field_0x1C = 0;
    pbis->field_0xC = 0;
    pbis->field_0x20 = 0;
    pbis->field_0x24 = 0;
    pbis->field_0x2C = 0;
    pbis->field_0x28 = 0;
    return pbis;
}
