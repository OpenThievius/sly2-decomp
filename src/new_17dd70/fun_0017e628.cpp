#include "sly2.h"
#include "goal.h"
extern "C" void* func_00205438(void*, int);
extern "C" QW PosLoWorld(void*);
extern "C" QW func_001C1EC0(void*, QW);
struct GOALMOVE : GOAL { u8 unknown_0x30[0x20]; QW pos; u8 unknown_0x60[8]; int mode; };
struct Route { u8 unknown_0x0[0x10]; void* guard; u8 unknown_0x14[0x30 - 0x14]; char* waypoints; int index; };
extern "C" void func_0017E628(Route* route)
{
    GOALMOVE* move = (GOALMOVE*)func_00205438(route->guard, 0xAC);
    move->mode = 1;
    char* waypoint = route->waypoints + (route->index * 0x20 + 0x60);
    move->pos = func_001C1EC0(waypoint, PosLoWorld(route->guard));
    move->Activate();
}
