#include "sly2.h"
struct CMovieText { u8 unknown_0x0[0x8]; void* font; u8 unknown_0xC[0x7C]; float gScale; };
extern "C" void CMovieText_Reset(CMovieText*, int);
extern "C" int CMovieText_ChNext(CMovieText*);
extern "C" float DxFromFontCh(void*, int);
static inline float GMax(float a, float b) { return a >? b; }
extern "C" float CMovieText_DxMaxLine(CMovieText* ptext)
{
    float dxMax = 0.0f;
    float dxLine = 0.0f;
    CMovieText_Reset(ptext, 0);
    int ch;
    while ((ch = CMovieText_ChNext(ptext)) != 0) {
        if (ch == '\n') {
            dxMax = GMax(dxLine, dxMax);
            dxLine = 0.0f;
        } else {
            dxLine = dxLine + DxFromFontCh(ptext->font, ch) * ptext->gScale;
        }
    }
    float r = GMax(dxLine, dxMax);
    dxMax = r;
    return dxMax;
}
