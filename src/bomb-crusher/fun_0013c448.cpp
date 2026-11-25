#include "loot.h"
/* func_0013C448's view of the selected LOOTDEF: a count and up to three words it appends (one reader) */
struct LOOTDEFSLOTS { u8 unknown_0x0[0x1C]; u32 cslot; s32 aslot[3]; };
void func_0013C448(LOOT *self, int value)
{
    LOOTDEFSLOTS *list = (LOOTDEFSLOTS *)self->plootdefSel;
    unsigned count = list->cslot;
    if (count < 3) {
        list->aslot[count] = value;
        list->cslot = count + 1;
    }
}
