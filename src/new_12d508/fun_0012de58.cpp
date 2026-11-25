#include "sly2.h"
#include "act.h"
extern "C" ACTVAL *PactNewForXf(int, int, int, int, int);
extern "C" void InsertXfAct(int, int, ACTVAL *);

extern "C" ACTVAL *func_0012DE58(float parameter, int palo, int pxf, int priority, QW pos, QW vel)
{
    ACTVAL *pact = PactNewForXf(8, palo, pxf, priority, 0x11);
    pact->tGoal = parameter;
    pact->posGoal = pos;
    pact->velGoal = vel;
    InsertXfAct(palo, pxf, pact);
    return pact;
}
