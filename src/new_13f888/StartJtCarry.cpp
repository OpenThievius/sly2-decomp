#include "sly2.h"
#include "jt.h"
extern "C" {
void FadeAloIn(void *, float);
QW PosLoWorld(void *);
void CarryThrow_UpdateArc(void *, int);
void CarryThrow_SetState(void *, int);
}
void StartJtCarry(JT *jt, void *palo, void *ploFrom)
{
    FadeAloIn(palo, 0.25f);
    jt->pgadgetLeased = (GADGETOBJ *)palo;
    jt->posCarryFrom = PosLoWorld(ploFrom);
    CarryThrow_UpdateArc(jt->PvCarry(), 0);
    jt->SetMode(7);
    CarryThrow_SetState(jt->PvCarry(), 7);
}
