#include "fbfont.h"
extern "C" {
s32 IglyphFromFontCh(MOVIEFONT *, s32);

f32 DxFromFontCh(MOVIEFONT *font, s32 ch) {
    f32 result;
    s32 iglyph;

    iglyph = IglyphFromFontCh(font, ch & 0xFF);
    if (iglyph != 0) {
        result = font->adx[iglyph - 1];
    } else {
        result = 0.0f;
    }
    return result;
}

}
