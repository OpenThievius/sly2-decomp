#include "sly2.h"
#include "act.h"
struct ACTREF { ACT act; ACT *pactRef; };
extern "C" ACT *PactNewForXf(int, ALO *, XF *, int, int);
extern "C" void InsertXfAct(ALO *, XF *, ACT *);

ACTREF *func_0012DD28(ALO *palo, XF *pxf, int priority, ACT *pactRef)
{
    int xfk = (pxf == pactRef->pxf) ? 0xE : 0xD;
    ACTREF *pact = (ACTREF *)PactNewForXf(7, palo, pxf, priority, xfk);
    pact->pactRef = pactRef;
    InsertXfAct(palo, pxf, &pact->act);
    return pact;
}
