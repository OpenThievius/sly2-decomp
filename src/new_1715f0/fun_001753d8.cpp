#include "types.h"
struct Obj { u8 unknown_0x0[0x10]; void *parent; u8 unknown_0x14[0x20]; int guard; };
extern "C" void func_001EEF68(Obj *);
extern "C" void AddGuardSgs(void *, int);
void func_001753D8(Obj *obj)
{
    func_001EEF68(obj);
    AddGuardSgs(obj->parent, 0x18);
    obj->guard = -1;
}
