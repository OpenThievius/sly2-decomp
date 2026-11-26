// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "rgba.h"
#include "fbsprite.h"
struct P16 { RGBA v; u8 unknown_0x4[12]; };
struct TMP { union { AFFINE2D dummy; struct { RGBA t0; u8 unknown_0x4[12]; RGBA t1; u8 unknown_0x14[12]; } c; } v; union { AFFINE2D lerped; struct { RGBA t2; u8 unknown_0x4[12]; RGBA t3; } c; } u; };
struct FRAME { AFFINE2D xf; P16 outAdd, outMul, s40, s50, s60; TMP tmp; };
extern "C" void ClearSle(void *);
extern "C" void ApplySpriteKeySounds(SPRITELABEL *, int, int);
extern "C" void func_002190F8(SPRITELABEL *, int, int);
extern "C" void ClearSpriteKeySlots(SPRITELABEL *, int, int);
extern "C" void PlaceSpriteKeyCharacters(float, float, SPRITELABEL *, int, int, AFFINE2D *, RGBA *, RGBA *);
extern "C" void func_002158C0(MOVIECHAR *, SLOT *);
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
static inline unsigned char LerpByte(int from, int to, float u)
{
    if (from == to) return to;
    if (from < to) return from + (int)(u * ((float)to + 0.999f - (float)from));
    float inv = 1.0f - u;
    return to + (int)(inv * ((float)from + 0.999f - (float)to));
}
static inline SPRITEINST *PinstFromLabel(SPRITELABEL *label, int iinst)
{
    return (SPRITEINST *)(iinst * sizeof(SPRITEINST) + (uptr)label->psprite->insts);
}
extern "C" void AdvanceSpriteInstance(float dt, SPRITELABEL *label, int iinst, AFFINE2D *pxf, RGBA *prgbaAdd, RGBA *prgbaMul)
{
    FRAME fr;
    SPRITEINST *inst;
    int cslot;
    SLOT *aslot;
    float tNow;
    int ikey;
    int firstPass;
    float tLast;
    cslot = PinstFromLabel(label, iinst)->cslot;
    ikey = (unsigned short)PinstFromLabel(label, iinst)->ikeyNext;
    firstPass = (ikey == 0);
    tNow = PinstFromLabel(label, iinst)->t;
    tLast = tNow;
    aslot = PinstFromLabel(label, iinst)->aslot;
    do {
        if (ikey < label->ckey) {
            SPRITEKEY *key = (__typeof__(&(label->akey)[0]))((ikey) * sizeof((label->akey)[0]) + (uptr)(label->akey));
            float tKey = key->t;
            if (tKey <= tNow) {
                tLast = tKey;
                ApplySpriteKeySounds(label, ikey, iinst);
                func_002190F8(label, ikey, iinst);
                ClearSpriteKeySlots(label, ikey, iinst);
                fr.s40.v = *prgbaAdd;
                fr.s50.v = *prgbaMul;
                PlaceSpriteKeyCharacters(tKey, dt, label, ikey, iinst, pxf, &fr.s40.v, &fr.s50.v);
                ikey++;
                inst = PinstFromLabel(label, iinst);
                inst->ikeyNext = inst->ikeyNext + 1;
                inst = PinstFromLabel(label, iinst);
                if (label->ckey < (unsigned short)inst->ikeyNext) {
                    inst->ikeyNext = label->ckey;
                }
            }
        }
        for (int islot = 0; islot < cslot; islot++) {
            SLOT *slot = &aslot[islot];
            if (slot->pchar == 0 || slot->tUpdated == tLast) continue;
            if (firstPass) {
                func_002158C0(slot->pchar, slot);
                continue;
            }
            if (slot->fTween != 0 && slot->pxfTo != 0) {
                float u = (tLast - slot->tFrom) / (slot->tTo - slot->tFrom);
                const float *from = &slot->pxfFrom->a;
                const float *to = &slot->pxfTo->a;
                float *out = &fr.tmp.u.lerped.a;
                for (int ig = 0; ig < 6; ig++) {
                    out[ig] = (1.0f - u) * from[ig] + u * to[ig];
                }
                fr.tmp.v.dummy = fr.tmp.u.lerped;
                fr.xf = fr.tmp.u.lerped;
                fr.tmp.v.c.t1 = slot->rgbaAddFrom;
                fr.tmp.u.c.t2 = slot->rgbaAddTo;
                fr.tmp.u.c.t3.r = LerpByte((unsigned char)fr.tmp.v.c.t1.r, (unsigned char)fr.tmp.u.c.t2.r, u);
                fr.tmp.u.c.t3.g = LerpByte((unsigned char)fr.tmp.v.c.t1.g, (unsigned char)fr.tmp.u.c.t2.g, u);
                fr.tmp.u.c.t3.b = LerpByte((unsigned char)fr.tmp.v.c.t1.b, (unsigned char)fr.tmp.u.c.t2.b, u);
                fr.tmp.u.c.t3.a = LerpByte((unsigned char)fr.tmp.v.c.t1.a, (unsigned char)fr.tmp.u.c.t2.a, u);
                fr.tmp.v.c.t0 = fr.tmp.u.c.t3;
                fr.s40.v = fr.tmp.v.c.t0;
                fr.tmp.v.c.t1 = slot->rgbaMulFrom;
                fr.tmp.u.c.t2 = slot->rgbaMulTo;
                fr.tmp.u.c.t3.r = LerpByte((unsigned char)fr.tmp.v.c.t1.r, (unsigned char)fr.tmp.u.c.t2.r, u);
                fr.tmp.u.c.t3.g = LerpByte((unsigned char)fr.tmp.v.c.t1.g, (unsigned char)fr.tmp.u.c.t2.g, u);
                fr.tmp.u.c.t3.b = LerpByte((unsigned char)fr.tmp.v.c.t1.b, (unsigned char)fr.tmp.u.c.t2.b, u);
                fr.tmp.u.c.t3.a = LerpByte((unsigned char)fr.tmp.v.c.t1.a, (unsigned char)fr.tmp.u.c.t2.a, u);
                fr.tmp.v.c.t0 = fr.tmp.u.c.t3;
                fr.s60.v = fr.tmp.v.c.t0;
            } else {
                fr.xf = *slot->pxfFrom;
                fr.s40.v = slot->rgbaAddFrom;
                fr.s60.v = slot->rgbaMulFrom;
            }
            fr.tmp.u.lerped.a = fr.xf.a * pxf->a + fr.xf.b * pxf->c;
            fr.tmp.u.lerped.b = fr.xf.a * pxf->b + fr.xf.b * pxf->d;
            fr.tmp.u.lerped.c = fr.xf.c * pxf->a + fr.xf.d * pxf->c;
            fr.tmp.u.lerped.d = fr.xf.c * pxf->b + fr.xf.d * pxf->d;
            fr.tmp.u.lerped.e = fr.xf.e * pxf->a + fr.xf.f * pxf->c + pxf->e;
            fr.tmp.u.lerped.f = fr.xf.e * pxf->b + fr.xf.f * pxf->d + pxf->f;
            fr.tmp.v.dummy = fr.tmp.u.lerped;
            fr.xf = fr.tmp.u.lerped;
            fr.tmp.v.c.t0 = *prgbaMul;
            fr.tmp.v.c.t1 = *prgbaAdd;
            fr.tmp.u.c.t2 = fr.s60.v;
            fr.tmp.u.c.t3 = fr.s40.v;
            CombineColorTransforms(&fr.tmp.v.c.t0, &fr.tmp.v.c.t1, &fr.tmp.u.c.t2, &fr.tmp.u.c.t3, &fr.outMul.v, &fr.outAdd.v);
            fr.tmp.v.c.t0 = fr.outAdd.v;
            fr.tmp.v.c.t1 = fr.outMul.v;
            func_00215850(slot->pchar, slot, dt, &fr.xf, &fr.tmp.v.c.t0, &fr.tmp.v.c.t1);
            slot->tUpdated = tLast;
            slot->xf = fr.xf;
            slot->rgbaAdd = fr.outAdd.v;
            slot->rgbaMul = fr.outMul.v;
            ClearSle(&slot->pslNext);
        }
        firstPass = 0;
    } while (ikey < label->ckey && label->akey[ikey].t <= tNow);
}
