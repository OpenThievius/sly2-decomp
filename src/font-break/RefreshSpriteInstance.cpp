#include "sly2.h"
#include "fbsprite.h"
struct TMP { union { AFFINE2D dummy; struct { RGBA t0; char p0[12]; RGBA t1; char p1[12]; } c; } v; union { AFFINE2D lerped; struct { RGBA t2; char p2[12]; RGBA t3; } c; } u; };
extern "C" void ClearSle(void *);
extern "C" void CombineColorTransforms(RGBA *, RGBA *, RGBA *, RGBA *, RGBA *, RGBA *);
extern "C" void func_00215850(MOVIECHAR *, SLOT *, float, AFFINE2D *, RGBA *, RGBA *);

static inline AFFINE2D Mult(const AFFINE2D &child, const AFFINE2D &parent)
{
    AFFINE2D product;
    float ca = child.a, cb = child.b, cc = child.c, cd = child.d, ce = child.e, cf = child.f;
    product.a = ca * parent.a + cb * parent.c;
    product.b = ca * parent.b + cb * parent.d;
    product.c = cc * parent.a + cd * parent.c;
    product.d = cc * parent.b + cd * parent.d;
    product.e = ce * parent.a + cf * parent.c + parent.e;
    product.f = ce * parent.b + cf * parent.d + parent.f;
    return product;
}
static inline float ItoF(int v) { return (float)v; }
// steer-ok: returns char, not unsigned char: the insn count before GCSE decides which of two equal-priority addresses gets the lower register (matching.md "Register allocation"); the code is otherwise identical
static inline char LerpByte(int from, int to, float u)
{
    if (from == to) return to;
    if (from < to) return from + (int)(u * (ItoF(to) + 0.999f - ItoF(from)));
    float inv = 1.0f - u;
    return to + (int)(inv * (ItoF(from) + 0.999f - ItoF(to)));
}
extern "C" void RefreshSpriteInstance(float dt, SPRITELABEL *label, int iinst, AFFINE2D *pxf, RGBA *prgbaAdd, RGBA *prgbaMul)
{
    SPRITEINST *inst = (SPRITEINST *)(iinst * sizeof(SPRITEINST) + (uptr)label->psprite->insts);
    SLOT *aslot = inst->aslot;
    int cslot = inst->cslot;
    float t = inst->t;
    for (int islot = 0; islot < cslot; islot++) {
        SLOT *slot = &aslot[islot];
        if (slot->pchar == 0) {
            slot->tUpdated = t;
            ClearSle(&slot->pslNext);
            continue;
        }
        AFFINE2D xf;
        RGBA outAdd, outMul;
        RGBA mulSlot, addSlot;
        TMP tmp;
        if (slot->fTween != 0 && slot->pxfTo != 0) {
            float u = (t - slot->tFrom) / (slot->tTo - slot->tFrom);
            const float *from = &slot->pxfFrom->a;
            const float *to = &slot->pxfTo->a;
            float *out = &tmp.u.lerped.a;
            for (int ig = 0; ig < 6; ig++) {
                out[ig] = (1.0f - u) * from[ig] + u * to[ig];
            }
            tmp.v.dummy = tmp.u.lerped;
            xf = tmp.u.lerped;
            tmp.v.c.t1 = slot->rgbaAddFrom;
            tmp.u.c.t2 = slot->rgbaAddTo;
            tmp.u.c.t3.r = LerpByte((unsigned char)tmp.v.c.t1.r, (unsigned char)tmp.u.c.t2.r, u);
            tmp.u.c.t3.g = LerpByte((unsigned char)tmp.v.c.t1.g, (unsigned char)tmp.u.c.t2.g, u);
            tmp.u.c.t3.b = LerpByte((unsigned char)tmp.v.c.t1.b, (unsigned char)tmp.u.c.t2.b, u);
            tmp.u.c.t3.a = LerpByte((unsigned char)tmp.v.c.t1.a, (unsigned char)tmp.u.c.t2.a, u);
            tmp.v.c.t0 = tmp.u.c.t3;
            addSlot = tmp.v.c.t0;
            tmp.v.c.t1 = slot->rgbaMulFrom;
            tmp.u.c.t2 = slot->rgbaMulTo;
            tmp.u.c.t3.r = LerpByte((unsigned char)tmp.v.c.t1.r, (unsigned char)tmp.u.c.t2.r, u);
            tmp.u.c.t3.g = LerpByte((unsigned char)tmp.v.c.t1.g, (unsigned char)tmp.u.c.t2.g, u);
            tmp.u.c.t3.b = LerpByte((unsigned char)tmp.v.c.t1.b, (unsigned char)tmp.u.c.t2.b, u);
            tmp.u.c.t3.a = LerpByte((unsigned char)tmp.v.c.t1.a, (unsigned char)tmp.u.c.t2.a, u);
            tmp.v.c.t0 = tmp.u.c.t3;
            mulSlot = tmp.v.c.t0;
        } else {
            xf = *slot->pxfFrom;
            addSlot = slot->rgbaAddFrom;
            mulSlot = slot->rgbaMulFrom;
        }
        tmp.u.lerped.a = xf.a * pxf->a + xf.b * pxf->c;
        tmp.u.lerped.b = xf.a * pxf->b + xf.b * pxf->d;
        tmp.u.lerped.c = xf.c * pxf->a + xf.d * pxf->c;
        tmp.u.lerped.d = xf.c * pxf->b + xf.d * pxf->d;
        tmp.u.lerped.e = xf.e * pxf->a + xf.f * pxf->c + pxf->e;
        tmp.u.lerped.f = xf.e * pxf->b + xf.f * pxf->d + pxf->f;
        tmp.v.dummy = tmp.u.lerped;
        xf = tmp.u.lerped;
        tmp.v.c.t0 = *prgbaMul;
        tmp.v.c.t1 = *prgbaAdd;
        tmp.u.c.t2 = mulSlot;
        tmp.u.c.t3 = addSlot;
        CombineColorTransforms(&tmp.v.c.t0, &tmp.v.c.t1, &tmp.u.c.t2, &tmp.u.c.t3, &outMul, &outAdd);
        if (slot->pchar != 0) {
            tmp.v.c.t0 = outAdd;
            tmp.v.c.t1 = outMul;
            func_00215850(slot->pchar, slot, dt, &xf, &tmp.v.c.t0, &tmp.v.c.t1);
        }
        slot->tUpdated = t;
        slot->xf = xf;
        slot->rgbaAdd = outAdd;
        slot->rgbaMul = outMul;
        ClearSle(&slot->pslNext);
    }
}
