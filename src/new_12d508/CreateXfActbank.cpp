#include "sly2.h"
#include "act.h"
extern "C" ACT *PactNewForXf(int, ALO *, XF *, int, int);
extern "C" void InsertXfAct(ALO *, XF *, ACT *);

ACT4 *CreateXfActbank(float uBank, float dtPredict, ALO *palo, XF *pxf, int priority, int xfk)
{
    ACT4 *pact = (ACT4 *)PactNewForXf(4, palo, pxf, priority, xfk);
    pact->field_0x1C = uBank; /* uBank */
    pact->field_0x20 = dtPredict; /* dtPredict */
    InsertXfAct(palo, pxf, &pact->act);
    return pact;
}
