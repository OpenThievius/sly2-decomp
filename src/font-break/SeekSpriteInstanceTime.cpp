#include "sly2.h"
#include "fbsprite.h"
extern "C" {
int FGetSpriteSlotTransform(SPRITEMOVIE *, int, AFFINE2D *, RGBA *, RGBA *, int, void *);
void ClearSpriteInstance(SPRITE *, int);
void UpdateSpriteInstance(float, SPRITE *, int, AFFINE2D *, RGBA *, RGBA *);
}
void SeekSpriteInstanceTime(float t, SPRITE *sprite, int iinst, SLOT *slot)
{
    struct { AFFINE2D mat; RGBA add[4]; RGBA mul[4]; RGBA ca[4]; RGBA cm[4]; RGBA cm2[4]; } l;
    if (sprite->insts[iinst].ilabel < 0)
        return;
    float dt = sprite->labels[sprite->insts[iinst].ilabel].dt;
    float lo = 0.0f;
    lo = lo < t ? t : lo;
    float tc = lo < dt ? lo : dt;
    if (slot != 0) {
        l.mat = slot->xf;
        l.add[0] = slot->rgbaAdd;
        l.mul[0] = slot->rgbaMul;
    } else {
        SPRITEMOVIE *movie = sprite->pmovie;
        int index = sprite - movie->asprite;
        if (!FGetSpriteSlotTransform(movie, index, &l.mat, l.add, l.mul, 0, 0))
            return;
    }
    ClearSpriteInstance(sprite, iinst);
    sprite->insts[iinst].t = 0.0f;
    sprite->insts[iinst].ikeyNext = 0;
    sprite->insts[iinst].fPaused = 0;
    l.ca[0] = l.add[0];
    l.cm[0] = l.mul[0];
    UpdateSpriteInstance(0.0f, sprite, iinst, &l.mat, l.ca, l.cm);
    sprite->insts[iinst].fPaused = 0;
    l.ca[0] = l.add[0];
    l.cm2[0] = l.mul[0];
    UpdateSpriteInstance(tc, sprite, iinst, &l.mat, l.ca, l.cm2);
    sprite->insts[iinst].fPaused = 1;
}
