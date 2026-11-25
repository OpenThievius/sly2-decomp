#include "sly2.h"
#include "act.h"
extern "C" ACT *PactNewForXf(int, ALO *, XF *, int, int);
extern "C" void InsertXfAct(ALO *, XF *, ACT *);

ACT1 *func_0012DC18(ALO *palo, XF *pxf, int priority, int xfk, int mode, QW point)
{
    ACT1 *pact = (ACT1 *)PactNewForXf(1, palo, pxf, priority, xfk);
    pact->field_0x1C = mode;
    pact->vec20 = point;
    InsertXfAct(palo, pxf, &pact->act);
    return pact;
}
