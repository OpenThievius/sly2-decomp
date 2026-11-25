#include "sly2.h"
struct B { B* owner; u8 unknown_0x4[0x1C]; float f20; };
struct A { u8 unknown_0x0[0x134]; B* p134; float f138; float f13C; };
void func_001F2688(A* a, float v)
{
    a->f13C = v;
    B* b = a->p134;
    if (b && (void*)b->owner == (void*)a) b->f20 = v;
}
