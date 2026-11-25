#include "types.h"
struct CMOVIETEXT { u8 unknown_0x0[0x84]; float dyLine; };
extern "C" {
int CMovieText_ClineWrap(void *);
float CMovieText_DxMaxLine(void *);

void CMovieText_GetExtents(CMOVIETEXT *text, float *width, float *height) {
    int lines = CMovieText_ClineWrap(text);
    float maxWidth = CMovieText_DxMaxLine(text);
    float lineHeight = (float)lines * text->dyLine;
    if (width) *width = maxWidth;
    if (height) *height = lineHeight;
}
}
