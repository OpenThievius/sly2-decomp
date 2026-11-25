#include "sly2.h"
#include "lo.h"
struct ROPE { u8 unknown_0x0[0x10]; void *plo[2]; u8 unknown_0x20_gap[8]; QW anchor[2]; void *xf[2]; void *crv; };
extern "C" char D_002C44F0;
extern "C" float UMinCrv(void *);
extern "C" float UMaxCrv(void *);
extern "C" void EvaluateCrvFromU(void *, float, void *, void *);
extern "C" void SetRopeSimEnd(ROPE *rope, int end, LO *plo)
{
    rope->plo[end] = plo;
    if (plo) {
        QW mat[4];
        rope->xf[end] = plo->Slot32(mat);
        *(rope->anchor + end) = mat[3];
    } else {
        rope->xf[end] = &D_002C44F0;
        float u;
        if (end == 0) u = UMinCrv(rope->crv);
        else u = UMaxCrv(rope->crv);
        EvaluateCrvFromU(rope->crv, u, &rope->anchor[end], 0);
    }
}
