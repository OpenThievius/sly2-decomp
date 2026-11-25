#include "types.h"
#include "ps2inline.h"
#include "sly.h"
extern "C" {
void func_00141588(SLY *, QW *);
QW PosLoWorld(void *);
}
void func_0018A350(SLY *pholder, QW *ppos)
{
    float *pcomponents = (float *)ppos;
    switch (pholder->jts) {
    case 3:
        func_00141588(pholder, ppos);
        pcomponents[2] = FloatFromWord(LaneWordZ(PosLoWorld(pholder->pjtcsinfo))) + -175.0f;
        break;
    case 0x16:
        func_00141588(pholder, ppos);
        pcomponents[2] = FloatFromWord(LaneWordZ(PosLoWorld(pholder->pjtcsinfo))) + -100.0f;
        break;
    case 0x15:
        *ppos = PosLoWorld(pholder);
        break;
    default:
        func_00141588(pholder, ppos);
        break;
    }
}
