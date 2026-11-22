// SPDX-License-Identifier: GPL-3.0-or-later
#include "cfont.h"

extern "C" GLYPH *PglyffFromCh__8CFontBrxc(CFONT *, unsigned char);

float DxFromCh__8CFontBrxc(CFONT *font, unsigned char character) {
    GLYPH *glyph;

    glyph = PglyffFromCh__8CFontBrxc(font, character);
    if (glyph != 0) {
        return (float)(glyph->width + 1) * font->scaleX;
    }
    return font->scaleX * (float)font->dxSpace;
}
