#include "sly2.h"
#include "hitfx.h"
// steer-ok: GMin keeps the constant as the first operand of the min, so its result shares the constant's register (matching.md "Register allocation"); same form as GMax in src/cm/RecalcCmFrustrum__FP2CM.cpp
static inline float GMin(float a, float b) { return a <? b; }
/* HitFx_GIntensity's view of the effect's definition: the intensity at 0x54, returned as is when the effect has no duration (one reader) */
struct HITFXDEFSCALE { u8 unknown_0x0[0x54]; f32 scale; };
extern "C" {
extern float g_2dded0;
extern float g_2bdce0;
extern float g_2bdcf0[3];
float HitFx_GIntensity(HITFX *fx)
{
    HITFXDEF *def = fx->pdef;
    HITFXDEFSCALE *view = (HITFXDEFSCALE *)def;
    float duration = def->duration;
    if (0.0f < duration) {
        float limit = g_2bdce0;
        float divisor = limit < duration ? limit : duration;
        float elapsed = g_2dded0 - fx->tStart;
        float t = GMin(1.0f, elapsed / divisor);
        return view->scale * (g_2bdcf0[0] + t * (g_2bdcf0[1] + t * g_2bdcf0[2]));
    }
    return view->scale;
}
}
