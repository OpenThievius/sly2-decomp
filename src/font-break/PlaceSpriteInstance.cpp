#include "sly2.h"
#include "fbsprite.h"
extern SPRITESTAMP g_2ddf18;
void StartSpriteInstance(float, SPRITE *, int, int, AFFINE2D *, RGBA *, RGBA *);

void PlaceSpriteInstance(SPRITE *s, int id, int iinst, AFFINE2D *xf, RGBA *add, RGBA *mul)
{
    float start = 0.0f;
    int ilabel;
    if (id == 0x314) {
        ilabel = s->ilabelPending;
        if (ilabel != -1) {
            s->ilabelPending = -1;
        } else {
            if (s->stamp.value == g_2ddf18.value) {
                start = s->tStopped;
                ilabel = s->ilabelStopped;
            } else {
                s->tStopped = 0.0f;
                ilabel = 0;
                s->ilabelStopped = 0;
            }
        }
    } else {
        for (ilabel = 0; ilabel < s->clabel; ilabel++) {
            if (s->labels[ilabel].id == id) break;
        }
        if (ilabel >= s->clabel) return;
    }
    RGBA a = *add;
    RGBA m = *mul;
    StartSpriteInstance(start, s, ilabel, iinst, xf, &a, &m);
}
