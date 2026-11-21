#include "types.h"
extern "C" void* g_2dded0;
extern "C" void SetAlertState(void* palert, int nState);
void SetAlertState(void* palert, int nState)
{
    float tNow = *(float*)(uptr)&g_2dded0;
    *(int*)(unsigned int)((uptr)palert + 8u) = nState;
    *(float*)(unsigned int)((uptr)palert + 4u) = tNow;
}
