#include "sly2.h"
extern "C" void func_001F4FB0(void *, void *);
/* an XF's words at 0x94 and 0x98 as this function clears them: two whole words (XF declares 0x98 as two halves) */
struct XFWORDS { u8 unknown_0x0[0x94]; s32 field_0x94; s32 field_0x98; };
void func_0017F1A0(void *punused, XFWORDS *pxf)
{
    func_001F4FB0(punused, pxf);
    pxf->field_0x94 = 0;
    pxf->field_0x98 = 0;
}
