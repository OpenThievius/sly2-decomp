#include "sly2.h"
#include "fade.h"
/* a view of SW up to the fade it keeps at 0x3E60 (sw.h has it as an s32, WarpJtToSafePoint passes it to StartFade) */
struct LEVEL { u8 unknown_0x0[0x3E60]; FADE *pfade; };
extern "C" FADE *PloNew(int, int, int, int);
void func_0020E338(LEVEL *plevel)
{
    plevel->pfade = PloNew(0x74, 0, -1, -1);
    plevel->pfade->d2 = 0.1f;
    plevel->pfade->d3 = 0.25f;
    plevel->pfade->rgbaC1 = 0x80200000;
    plevel->pfade->kind = 1;
    plevel->pfade->Remove();
}
