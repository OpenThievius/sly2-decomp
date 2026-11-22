/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cfont.h"

void PopScaling__5CFont(struct CFONT *font) {
    s32 depth;
    struct CFONTSCALE *scale;

    depth = font->scaleDepth - 1;
    font->scaleDepth = depth;
    scale = &font->ascale[depth];
    font->scaleX = (f32) scale->sx;
    font->scaleY = (f32) scale->sy;
}
