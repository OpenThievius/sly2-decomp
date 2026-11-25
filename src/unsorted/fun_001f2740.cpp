// 0x1F2740 GetSoSphereKind
#include "so.h"
int func_001F2740(SO *pso)
{
    int grfso = pso->grfso;
    return (grfso << 8) >> 28;
}
