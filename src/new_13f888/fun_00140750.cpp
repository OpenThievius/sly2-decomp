// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
struct CLOCK_140750 { float t; float dt; };
extern "C" {
extern CLOCK_140750 g_2dded0;
extern const float D_002BCC6C;
extern const float D_002BCC70;
extern const float D_002BCC74;
extern const float D_002BCC78;
int func_001409E8(JT *);
QW PosLoWorld(void *);
void PhitfxSpawn_156548(void *parms, QW pos, void *owner, void **out);
}

static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (hi < g)
        return hi;
    return g;
}

extern "C" void func_00140750(JT *jt)
{
    if (jt->hitfxParms) {
        switch (func_001409E8(jt)) {
        case 1: {
            float dt = g_2dded0.dt;
            float value = jt->field_0x10CC + D_002BCC6C * dt;
            jt->field_0x10CC = value < 1.0f ? value : 1.0f;
            break;
        }
        case 0: {
            float dt = g_2dded0.dt;
            float value = jt->field_0x10CC + D_002BCC70 * dt;
            jt->field_0x10CC = value > 0.0f ? value : 0.0f;
            break;
        }
        case 2:
            jt->field_0x10CC = 0.0f;
            break;
        }
        if (jt->zapState != -1 || jt->field_0x10CC == 0.0f)
            jt->field_0x10C8 = -1;
        else if (jt->field_0x10CC == 1.0f || (jt->field_0x10C8 == 1 && jt->field_0x10CC > 0.0f))
            jt->field_0x10C8 = 1;
        else
            jt->field_0x10C8 = 0;
        int mode = jt->Slot98();
        if (jt->field_0x10C8 != 1 && mode == 1)
            mode = 2;
        switch (mode) {
        case 0:
            jt->field_0x10D0 = 0.0f;
            break;
        case 1: {
            float dt = g_2dded0.dt;
            jt->field_0x10D0 = GClamp(jt->field_0x10D0 + D_002BCC74 * dt, 0.0f, 1.0f);
            break;
        }
        case 2:
        case -1: {
            float dt = g_2dded0.dt;
            jt->field_0x10D0 = GClamp(jt->field_0x10D0 + D_002BCC78 * dt, 0.0f, 1.0f);
            break;
        }
        }
        if (jt->field_0x10D0 == 1.0f)
            PhitfxSpawn_156548(jt->hitfxParms, PosLoWorld(jt), jt, 0);
    }
}
