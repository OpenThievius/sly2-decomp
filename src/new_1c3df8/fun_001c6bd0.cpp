#include "dprize.h"
#include "clock.h"
extern "C" void func_001A58D0(DPRIZE *, int, int);
extern "C" const char RO_002A2D00[];
extern "C" const float g_2a7758;
void func_001C6BD0(DPRIZE *pdprize, QW pos, QW vel, float dtDelay, float dtLife)
{
    pdprize->Add();
    func_001A58D0(pdprize, 0, 0);
    pdprize->TranslateToPos(pos);
    pdprize->Slot30((void *)RO_002A2D00);
    VECTOR *vecLinear = (VECTOR *)&pdprize->pxfLinear->vel;
    vecLinear->z = 0;
    vecLinear->y = 0;
    vecLinear->x = 0;
    VECTOR *vecAngular = (VECTOR *)&pdprize->pxfAngular->vel;
    vecAngular->z = 0;
    vecAngular->y = 0;
    vecAngular->x = 0;
    pdprize->dtDelay = dtDelay;
    pdprize->landing = 0;
    pdprize->SetDprizes(3);
    *(QW *)&pdprize->velocity = vel;
    float expire = g_2a7758;
    if (dtLife != g_2a7758)
        expire = g_2dded0.t + dtLife;
    pdprize->tExpire = expire;
}
