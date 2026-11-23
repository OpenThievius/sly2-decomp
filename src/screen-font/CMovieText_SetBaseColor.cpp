#include "rgba.h"
extern "C" {
struct MOVIETEXT_215D00 { char pad[0x14]; struct RGBA colorShadow; struct RGBA base; };
void CMovieText_UpdateFont(void *);

void CMovieText_SetBaseColor(void *pThis, const void *pColor)
{
    struct MOVIETEXT_215D00 *pText = (struct MOVIETEXT_215D00 *)pThis;
    pText->base = *(const struct RGBA *)pColor;
    pText->colorShadow = pText->base;
    CMovieText_UpdateFont(pThis);
}
}
