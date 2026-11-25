#include "lo.h"
#include "xf.h"
extern f32 D_002C44E0[];
extern "C" void InvalidateXfSegment(LO *obj, XF *seg);
extern "C" void InvalidateXfSegment(LO *obj, XF *seg)
{
    switch (seg->kind) {
    case 0: case 1: case 2: case 3:
    case 13: case 14: case 15: case 16:
    case 20: case 21:
        break;
    default:
        seg->tMax = -3.4028235e38f;
        seg->ptMax = D_002C44E0;
        seg->tMin = -3.4028235e38f;
        seg->ptMin = D_002C44E0;
        break;
    }
    seg->sub = 0;
    obj->SetGrfField(4);
}
