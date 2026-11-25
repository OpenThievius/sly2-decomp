#include "cfont.h"
struct CFont : CFONT {
    void PushScaling(float rx, float ry);
};
void CFont::PushScaling(float rx, float ry)
{
    CFONTSCALE *psc = &ascale[scaleDepth++];
    psc->sx = scaleX;
    psc->sy = scaleX;
    scaleX = ascale[0].sx * rx;
    scaleY = ascale[0].sy * ry;
}
