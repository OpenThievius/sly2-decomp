// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"

extern "C" {
void RenderGlobset(void *pglobset, void *pcm, float uAlpha, float uAlphaOther, RO *pro);
void func_001F3C10(SO *pso);
extern s32 g_2ddf54;

void func_001F3C70(SO *pso) {
    if (((u8 *)&pso->grfo)[5] & g_2ddf54) {
        func_001F3C10(pso);
        RenderGlobset(&pso->field_0x80, 0, pso->uFade, pso->uFade, pso->field_0x134);
    }
}
}
