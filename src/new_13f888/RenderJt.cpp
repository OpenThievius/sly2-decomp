#include "sly2.h"
#include "sly.h"

struct SmoothParam { float a; float b; float c; };

extern "C" {
extern unsigned int g_2ddf54;
extern float g_2dded0[];
extern const float D_FLT_002BD268;
extern const float D_FLT_002BD26C;
extern SmoothParam D_002BD270;
extern SLY *g_2e1e40;
void func_001F3C10(JT *);
float GSmooth__FfffP3SMPPf(float, float, float, SmoothParam *, float *);
void RenderGlobset(void *, void *, void *, float, float);
}

extern "C" void RenderJt(JT *pjt)
{
    if ((*((u8 *)&pjt->grfo + 5) & g_2ddf54) == 0) return;
    func_001F3C10(pjt);
    if (pjt->binocState == 1 && pjt->binocPhase != 2) return;
    float goalA;
    float goalB;
    if (pjt->attachKind == 2) {
        goalA = D_FLT_002BD268;
        goalB = D_FLT_002BD26C;
    } else {
        goalB = 1.0f;
        goalA = goalB;
    }
    pjt->field_0x10D4 = GSmooth__FfffP3SMPPf(pjt->field_0x10D4, goalA, g_2dded0[1], &D_002BD270, 0);
    pjt->field_0x10D8 = GSmooth__FfffP3SMPPf(pjt->field_0x10D8, goalB, g_2dded0[1], &D_002BD270, 0);
    if (pjt == g_2e1e40) {
        ((SO *)g_2e1e40->apartHide[0])->uFade = pjt->field_0x10D4;
        ((SO *)g_2e1e40->apartHide[1])->uFade = pjt->field_0x10D4;
    }
    float uFade = pjt->uFade;
    RenderGlobset(&pjt->field_0x80, 0, pjt->field_0x134, uFade * pjt->field_0x10D4, uFade * pjt->field_0x10D8);
}
