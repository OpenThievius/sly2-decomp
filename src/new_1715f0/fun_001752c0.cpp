#include "types.h"
struct Parent { u8 unknown_0x0[0xF3C]; int value; };
struct Obj { u8 unknown_0x0[0x10]; Parent *parent; };
extern "C" void func_00174B28(Obj *);
void func_001752C0(Obj *obj)
{
    func_00174B28(obj);
    obj->parent->value = 0;
}
