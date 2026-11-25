#include "types.h"
#include "cmpeg.h"
extern "C" unsigned int func_001AE150(int);
extern "C" SUBTITLE *func_001B2820(MOVIE *);

int FPlayQueuedMovies(CMpeg *pmpeg)
{
    if (pmpeg->cmovie <= 0)
        return 0;
    if (func_001AE150(1) < 0x41FC40) {
        pmpeg->cmovie = 0;
        return 0;
    }
    for (int imovie = 0; imovie < pmpeg->cmovie; imovie++) {
        MOVIE *pmovie = &pmpeg->amovie[imovie];
        pmpeg->psubtitle = func_001B2820(pmovie);
        do {
            pmpeg->Execute(pmovie);
        } while (pmpeg->fSkippable != 0);
        pmpeg->psubtitle = 0;
    }
    pmpeg->cmovie = 0;
    return 1;
}
