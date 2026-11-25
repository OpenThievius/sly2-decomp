#include "sly2.h"
struct SMACKI { QW posTarget; QW vTarget; };
struct SMACK { u8 unknown_0x0[0x14]; float tCreated; float dtLifetime; u8 unknown_0x1C[0x54]; QW pos; QW posPrev; QW v; u8 unknown_0xA0[0x50]; SMACKI *psmacki; u8 unknown_0xF4[0xC]; QW posScreen; };
extern "C" {
extern float g_2dded0[2];
extern char B_002DDF40[];
void EvaluateBezierPos__FfffP6VECTORN63(float, float, float, QW, QW, QW, QW, QW *, QW *, void *);
QW ConvertCmScreenToWorld(void *, QW);
}

void ProjectSmackTransform(SMACK *psmack, float dt)
{
    float dtRemaining = psmack->tCreated + psmack->dtLifetime - g_2dded0[0];
    float dtMin = g_2dded0[1];
    float dtSegment = dtRemaining < dtMin ? dtMin : dtRemaining;
    EvaluateBezierPos__FfffP6VECTORN63(dtSegment, dtMin, 1.0f, psmack->posScreen, psmack->v, psmack->psmacki->posTarget,
                                       psmack->psmacki->vTarget, &psmack->posScreen, &psmack->v, 0);
    psmack->posPrev = psmack->pos;
    psmack->pos = ConvertCmScreenToWorld(B_002DDF40, psmack->posScreen);
}
