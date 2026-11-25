#include "sly2.h"
struct CARRY { u8 unknown_0x0[0x18]; void *crvA; u8 unknown_0x1C[0x10]; void *crvB; };
extern "C" {
void EvaluateCrvFromU(void *, float, QW *, void *);
void ClosestPointOnSegment(QW, QW, QW, void *, float *, float *);
}

void func_001CC1F8(CARRY *pcarry, float u, QW pos, float *pu, float *ps)
{
    QW posA;
    QW posB;
    EvaluateCrvFromU(pcarry->crvA, u, &posA, 0);
    EvaluateCrvFromU(pcarry->crvB, u, &posB, 0);
    ClosestPointOnSegment(pos, posA, posB, 0, pu, ps);
}
