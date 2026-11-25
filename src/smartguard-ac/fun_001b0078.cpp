#include "pausemenu.h"
extern "C" PAUSEITEM D_002BFDA8[], D_002BFE08[], D_002BFE68[];
extern "C" int CGc_FFindScreen(void *);
int func_001B0078(PAUSEMENU *pmenu)
{
    if (CGc_FFindScreen(pmenu) == 0)
        return -1;
    int depth = pmenu->depth;
    if (depth <= 0)
        return -1;
    PAUSEITEM *aitem = pmenu->apage[depth - 1].aitem;
    if (aitem == D_002BFDA8)
        return 0x1E;
    if (aitem != D_002BFE08)
        return aitem != D_002BFE68 ? -1 : 0x19;
    return 0x1F;
}
