// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "fbsprite.h"
struct L { AFFINE2D composed; QW add; QW mul; };
extern "C" void AdvanceSpriteInstance(SPRITELABEL *plabel, int iinst, AFFINE2D *pxf, QW *padd, QW *pmul, float t);
void StartSpriteInstance(float t, SPRITE *psprite, int ilabel, int iinst, AFFINE2D *pxf, RGBA *padd, RGBA *pmul)
{
    SPRITEINST *pinst = psprite->insts + iinst;
    pinst->ilabel = ilabel;
    pinst->fPaused = 0;
    pinst->t = t;
    pinst->ikeyNext = 0;
    L l;
    AFFINE2D *pxfcall;
    if (psprite->pxf) {
        AFFINE2D *pv = psprite->pxf;
        AFFINE2D tmp;
        float xa = pxf->a, xb = pxf->b, xc = pxf->c, xd = pxf->d, xe = pxf->e, xf = pxf->f;
        tmp.a = xa * pv->a + xb * pv->c;
        tmp.b = xa * pv->b + xb * pv->d;
        tmp.c = xc * pv->a + xd * pv->c;
        tmp.d = xc * pv->b + xd * pv->d;
        tmp.e = xe * pv->a + xf * pv->c + pv->e;
        tmp.f = xe * pv->b + xf * pv->d + pv->f;
        l.add = ((QW *)&tmp)[0];
        l.mul = ((QW *)&tmp)[1];
        l.composed = tmp;
        pxfcall = &l.composed;
    } else {
        pxfcall = pxf;
    }
    *(RGBA *)&l.add = *padd;
    *(RGBA *)&l.mul = *pmul;
    AdvanceSpriteInstance(psprite->labels + pinst->ilabel, iinst, pxfcall, &l.add, &l.mul, t);
}
