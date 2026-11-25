#include "types.h"
struct Other { u8 unknown_0x0[0x20]; QW a; QW b; u8 unknown_0x40[4]; int link; u8 unknown_0x48[0xC]; int state; };
struct Obj { u8 unknown_0x0[0x10]; int key; u8 unknown_0x14[0x30]; Other *other; };
QW func_00172760(Obj *obj)
{
    Other *other = obj->other;
    if (other->state == 4 && other->link == obj->key)
        return other->a;
    return obj->other->b;
}
