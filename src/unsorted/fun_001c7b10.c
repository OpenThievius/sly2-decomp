/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Getter: returns the int at +0x244 of its argument. Retail is `jr $ra` with the `lw` in the delay slot; the 8 bytes were lumped with the epilogue
   of SelectCoinLootDef above (its `addiu $sp` delay slot and a padding `nop`) until the boundary was cut at 0x1C7B10. */
#include "types.h"
/* the object's class is not known: only the int at 0x244 this getter reads */
struct INTHOLDER_1C7B10 {
    u8 unknown_0x0[0x244];
    s32 value;
};
int func_001C7B10(struct INTHOLDER_1C7B10 *self)
{
    return self->value;
}
