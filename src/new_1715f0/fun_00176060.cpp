#include "types.h"
struct Parent { u8 unknown_0x0[0x3CC]; int handle; u8 unknown_0x3D0[4]; int blocked; };
struct Obj { u8 unknown_0x0[0x10]; Parent *parent; u8 unknown_0x14[0x2C]; int busy; };
extern "C" int func_0020A7E0(int);
int func_00176060(Obj *obj)
{
    int result;
    if (obj->busy) {
        result = 0;
    } else {
        Parent *parent = obj->parent;
        if (parent->blocked)
            result = 0;
        else
            result = func_0020A7E0(parent->handle);
    }
    return result;
}
