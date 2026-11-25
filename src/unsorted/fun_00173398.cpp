#include "types.h"
struct Obj { u8 unknown_0x0[0x90]; s32 count; s32 *items; };
void func_00173398(Obj *obj, int item)
{
    int n = obj->count;
    if (n < 8) {
        obj->items[n] = item;
        obj->count = n + 1;
    }
}
