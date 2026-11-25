#include "sly2.h"
#include "act.h"
extern float g_2dded0;
extern "C" void EvaluateBezierPos__FfffP6VECTORN63(float, float, float, QW, QW, QW, QW, QW *, QW *, QW *);

void GetActvalPositionGoal(ACTVAL *pact, float dt, QW *pvecPos, QW *pvecVel)
{
    XF *pxf = pact->act.pxf;
    float tEnd = pxf->tArrive;
    if (tEnd <= g_2dded0 + dt) {
        if (pvecPos != 0)
            *pvecPos = pact->posGoal;
        if (pvecVel != 0)
            *pvecVel = pact->velGoal;
    } else {
        EvaluateBezierPos__FfffP6VECTORN63(tEnd - g_2dded0, dt, 1.0f, pxf->mat.row[3], pxf->vel, pact->posGoal, pact->velGoal, pvecPos, pvecVel, 0);
    }
}
