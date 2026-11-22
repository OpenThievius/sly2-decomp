// SPDX-License-Identifier: GPL-3.0-or-later
#include "po.h"

// KEYPAD: a PO subclass (config/recovered/decomp_names.md: InitKeypad is slot 0x38 of one). Local name and local fields
// only; its size is unknown, the padding places the fields this one function writes.
struct KEYPAD : PO {
    s32 field_0x180;
    u8 unknown_0x184[0x10];
    s32 field_0x194;
    u8 unknown_0x198[0x58];
    s32 field_0x1F0;
    s32 field_0x1F4;
    s32 field_0x1F8;
    s32 field_0x1FC;
    s32 field_0x200;
};
extern "C" void InitPo(PO *po);

// Tag test of the word at +0x40: true when bit 0 is clear (the word is a pointer).
static inline bool FIsPointer(int flags) { return (flags & 1) == 0; }

// Retail: InitPo(po), then +0x1F0 = 0x7B and six fields = -1, and bit 2 set
// in the tagged word at +0x40 (through the pointer when bit 0 is clear, in
// place otherwise). The test is `xori 1; andi 1; beqz` with the andi
// scheduled two slots after the xori: the tag test is a bool returned by an
// inline helper. A direct `(flags & 1) == 0` gives andi + bnez, and the
// open-coded `(flags ^ 1) & 1` keeps the andi right after the xori (score 2).
extern "C" void func_001C8280(KEYPAD *po)
{
    InitPo(po);
    po->field_0x1F0 = 0x7B;
    po->field_0x1FC = -1;
    po->field_0x1F8 = -1;
    po->field_0x1F4 = -1;
    po->field_0x200 = -1;
    po->field_0x180 = -1;
    po->field_0x194 = -1;
    int flags = po->grfSw;
    if (FIsPointer(flags)) {
        *(int *)flags |= 2;
    } else {
        po->grfSw = flags | 2;
    }
}
