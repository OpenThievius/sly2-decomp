#include "sly2.h"
#include "memcard.h"
extern "C" int sceMcGetInfo(int, int, int *, int *, int *);
extern "C" int McSync(void *, int, int, int *);
int GetCardFreeBytes(SAVE *psave, int *pcbFree)
{
    MEMCARD *pmc = &psave->mc;
    int nStart = sceMcGetInfo(psave->port, psave->slot, &psave->cardType, &psave->cFree, &psave->formatted);
    int nError = McSync(pmc, nStart, 1, 0);
    switch (nError) {
    case 9:
        nError = 0;
        break;
    case 10:
        nError = 0xC;
        break;
    }
    if (nError == 0)
        *pcbFree = psave->cFree << 10;
    else
        *pcbFree = 0;
    return nError;
}
