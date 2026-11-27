#include "sly2.h"
#include "fade.h"
#include "sw.h"
extern "C" FADE *PloNew(int, int, int, int);
void func_0020E338(SW *psw)
{
    psw->pfade = PloNew(0x74, 0, -1, -1);
    psw->pfade->d2 = 0.1f;
    psw->pfade->d3 = 0.25f;
    psw->pfade->rgbaC1 = 0x80200000;
    psw->pfade->kind = 1;
    psw->pfade->Remove();
}
