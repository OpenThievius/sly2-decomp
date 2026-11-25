#include "types.h"
struct Item_1D3FA8 { u8 unknown_0x0[0x14]; int id; };
struct Owner_1D3FA8 { u8 unknown_0x0[0x4F8]; int count; Item_1D3FA8 *items[1]; };
extern "C" Item_1D3FA8 *func_001D3FA8(Owner_1D3FA8 *owner, int id)
{
    for (int i = 0; i < owner->count; i++) {
        if (owner->items[i]->id == id)
            return owner->items[i];
    }
    return 0;
}
