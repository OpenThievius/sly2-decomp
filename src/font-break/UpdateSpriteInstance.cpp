#include "sly2.h"
#include "fbsprite.h"
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
extern "C" void AdvanceSpriteInstance(float, SPRITELABEL *, int, AFFINE2D *, RGBA *, RGBA *);
extern "C" void RefreshSpriteInstance(float, SPRITELABEL *, int, AFFINE2D *, RGBA *, RGBA *);
extern "C" void UpdateSpriteInstance(float dt, SPRITE *sprite, int iinst, AFFINE2D *xf, RGBA *rgbaAdd, RGBA *rgbaMul)
{
    SPRITEINST *inst = &sprite->insts[iinst];
    int ilabel = inst->ilabel;
    if (ilabel < 0) return;
    AFFINE2D composed;
    AFFINE2D *xfUse;
    if (sprite->pxf) {
        composed = Mult(*xf, *sprite->pxf);
        xfUse = &composed;
    } else {
        xfUse = xf;
    }
    if (inst->fPaused != 0) {
        RGBA add = *rgbaAdd;
        RGBA mul = *rgbaMul;
        RefreshSpriteInstance(dt, &sprite->labels[ilabel], iinst, xfUse, &add, &mul);
    } else {
        if (sprite->labels[ilabel].dt <= inst->t) {
            inst->t = 0.0f;
            inst->ikeyNext = 0;
        } else {
            inst->t = inst->t + dt;
        }
        RGBA add = *rgbaAdd;
        RGBA mul = *rgbaMul;
        AdvanceSpriteInstance(dt, &sprite->labels[ilabel], iinst, xfUse, &add, &mul);
    }
}
