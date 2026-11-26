// SPDX-License-Identifier: GPL-3.0-or-later
#include "fbsprite.h"
struct DMAS_213300 { unsigned base; int pad4[2]; char *p; };
struct Ctx_213300 { int kind; int pad4; float z; int padC; float add[4]; float mul[4]; };
extern "C" {
void func_001A5ED8(BLOT *);
int FDrawBlotMovie(BLOT *);
void func_002185D0(int);
void BuildBlotDmaHeader(BLOT *);
void func_00217298(BLOT *, int, float);
void DrawMovieCharacter(void *, void *, Ctx_213300 *, int);
void ClearSl(void *);
extern DMAS_213300 g_2dea28;
}
static inline void Pad64(DMAS_213300 *dmas) {
    while ((sptr)dmas->p & 0x3F) { *(int *)dmas->p = 0; dmas->p = dmas->p + 4; }
}
static inline void Uncache(DMAS_213300 *dmas) {
    Pad64(dmas);
    dmas->p = (char *)((uptr)dmas->p | 0x30000000);
    dmas->base |= 0x30000000;
}
static inline void Recache(DMAS_213300 *dmas) {
    Pad64(dmas);
    dmas->p = (char *)((uptr)dmas->p & 0x0FFFFFFF);
    dmas->base &= 0x0FFFFFFF;
}
static inline float Clamp(float value, float low, float high) {
    float result = value > high ? high : value;
    return result < low ? low : result;
}
static inline void FillColors(Ctx_213300 *ctx, SLOT *node) {
    float fr = (float)node->rgbaAdd.r - 127.0f, fg = (float)node->rgbaAdd.g - 127.0f;
    float fb = (float)node->rgbaAdd.b - 127.0f, fa = (float)node->rgbaAdd.a - 127.0f;
    ctx->add[0] = fr;
    ctx->add[1] = fg;
    ctx->add[2] = fb;
    ctx->add[3] = fa;
    int r, g, b, a;
    r = node->rgbaMul.r - 0x7F; g = node->rgbaMul.g - 0x7F; b = node->rgbaMul.b - 0x7F; a = node->rgbaMul.a - 0x7F;
    ctx->mul[0] = Clamp((float)r * 0.007874016f, -1.0f, 1.0f);
    ctx->mul[1] = Clamp((float)g * 0.007874016f, -1.0f, 1.0f);
    ctx->mul[2] = Clamp((float)b * 0.007874016f, -1.0f, 1.0f);
    ctx->mul[3] = Clamp((float)a * 0.007874016f, -1.0f, 1.0f);
}
extern "C" void DrawBlotMovie(BLOT *self)
{
    func_001A5ED8(self);
    if (!FDrawBlotMovie(self)) return;
    float z = 16.0f;
    func_002185D0(self->asprite);
    Uncache(&g_2dea28);
    BuildBlotDmaHeader(self);
    SLOT *prev = 0;
    Ctx_213300 ctx[2];
    for (SLOT *node = (SLOT *)self->sl.pvFirst; node; node = (SLOT *)node->pslNext, z += 1024.0f) {
        if (node->maskMode == 1) {
            ctx[0].add[0] = 0; ctx[0].add[1] = 0; ctx[0].add[2] = 0; ctx[0].add[3] = 0;
            ctx[0].mul[0] = 0; ctx[0].mul[1] = 0; ctx[0].mul[2] = 0; ctx[0].mul[3] = 0;
            ctx[0].z = z;
            ctx[0].kind = 1;
            prev = node;
            func_00217298(self, 1, z - 1.0f);
            DrawMovieCharacter(node->pchar, &node->xf, &ctx[0], node->flag);
            func_00217298(self, 3, ctx[0].z + 1.0f);
        } else if (node->maskMode == 4) {
            ctx[0].add[0] = 0; ctx[0].add[1] = 0; ctx[0].add[2] = 0; ctx[0].add[3] = 0;
            ctx[0].mul[0] = 0; ctx[0].mul[1] = 0; ctx[0].mul[2] = 0; ctx[0].mul[3] = 0;
            ctx[0].z = z;
            ctx[0].kind = 1;
            func_00217298(self, 2, z - 1.0f);
            DrawMovieCharacter(prev->pchar, &prev->xf, &ctx[0], prev->flag);
            prev = 0;
            func_00217298(self, 4, ctx[0].z + 1.0f);
            if (node->pchar) {
                FillColors(&ctx[1], node);
                z += 1024.0f;
                ctx[1].z = z;
                ctx[1].kind = 1;
                DrawMovieCharacter(node->pchar, &node->xf, &ctx[1], node->flag);
            }
        } else if (node->pchar) {
            FillColors(&ctx[0], node);
            ctx[0].z = z;
            ctx[0].kind = 1;
            DrawMovieCharacter(node->pchar, &node->xf, &ctx[0], node->flag);
        }
    }
    Recache(&g_2dea28);
    SLOT *node = (SLOT *)self->sl.pvFirst;
    while (node) {
        SLOT *cur = node;
        node = (SLOT *)node->pslNext;
        cur->pslNext = 0;
    }
    ClearSl(&self->sl);
}
