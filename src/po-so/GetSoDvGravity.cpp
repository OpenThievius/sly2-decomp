#include "sly2.h"
extern QW g_2a2dd0;
struct B { u8 unknown_0x0[0x80]; QW v; };
struct A { u8 unknown_0x0[0xE8]; B* p; };
QW GetSoDvGravity(A* a)
{
    if (!a->p) return g_2a2dd0;
    return a->p->v;
}
