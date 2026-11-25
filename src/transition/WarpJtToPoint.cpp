#include "jt.h"
/* a safe point: WarpJtToSafePoint copies its two quadwords into the JT (jt.h field_0x490, field_0x4A0) */
struct SAFEPT { void *pbasic; s32 field4; u8 unknown_0x8[0x8]; QW second; };
void *memset(void *, int, unsigned int);
extern "C" void WarpJtToSafePoint(JT *, SAFEPT *);
extern "C" void WarpJtToPoint(JT *pjt, QW pos)
{
    SAFEPT safe;
    memset(&safe, 0, 0x20);
    safe.second = pos;
    WarpJtToSafePoint(pjt, &safe);
}
