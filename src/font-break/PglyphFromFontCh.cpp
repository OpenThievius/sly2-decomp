#include "fbfont.h"
extern "C" {
s32 IglyphFromFontCh(MOVIEFONT *, s32);

MOVIEGLYPH *PglyphFromFontCh(MOVIEFONT *font, s32 ch) {
    MOVIEGLYPH *result;
    s32 iglyph;

    iglyph = IglyphFromFontCh(font, ch & 0xFF);
    if (iglyph != 0) {
        result = font->aglyph + iglyph;
    } else {
        result = 0;
    }
    return result;
}

}
