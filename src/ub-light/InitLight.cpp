#include "light.h"
#include "sw.h"
extern "C" void InitXfm(LIGHT *);
extern "C" void func_001A6CA8(LIGHT *, int);
extern "C" void InitLight(LIGHT *light)
{
    InitXfm(light);
    light->mode = 0;
    light->generation = -1;
    light->index = -1;
    light->rangeA = 200.0f;
    light->rangeB = 2000.0f;
    light->cone = 240.0f;
    light->field_0x158 = 1;
    func_001A6CA8(light, 1);
    int flags = light->grfSw;
    if (!(flags & 1))
        *(s32 *)&light->pgrfentry->grf &= ~0x20;
    else
        light->grfSw = flags & ~0x20;
}
