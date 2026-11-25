#include "types.h"
#include "vu0inline.h"
#include "sly2.h"
#include "fbsprite.h"
struct CM;
extern "C" const AFFINE2D RO_002A3A10;
extern CM B_002DDF40;
extern "C" QW PosLoWorld(void *);
extern "C" QW ConvertCmWorldToScreen(CM *, QW);
extern "C" void UpdateSpriteInstance(SPRITE *, float, int, AFFINE2D *, unsigned *, unsigned *);
#include "ps2inline.h"

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
extern "C" void UpdateRootSprite(float dt, SPRITE *sprite)
{
    if (sprite->fRoot == 0) return;
    AFFINE2D xf = RO_002A3A10;
    if (sprite->pmovie->plo != 0) {
        QW pos = PosLoWorld(sprite->pmovie->plo);
        QW screen = ConvertCmWorldToScreen(&B_002DDF40, pos);
        float x = LaneX(screen) * 320.0f;
        float y = LaneYInGeneralRegister(screen) * -246.40001f;
        xf.e = x + 320.0f;
        xf.f = y + 246.40001f;
    }
    if (sprite->pmovie->pxf != 0) {
        xf = Mult(xf, *sprite->pmovie->pxf);
    }
    unsigned add[4];
    unsigned mul[4];
    add[0] = 0x7F7F7F7F;
    mul[0] = 0xFFFFFFFF;
    UpdateSpriteInstance(sprite, dt, 0, &xf, add, mul);
}
