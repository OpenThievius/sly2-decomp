#include "types.h"
struct Obj { u8 unknown_0x0[0x30]; int a; u8 unknown_0x34[8]; int b; };
extern "C" void func_001EEF68(Obj *);
void func_00174920(Obj *obj)
{
    func_001EEF68(obj);
    obj->b = 0;
    obj->a = -1;
}
