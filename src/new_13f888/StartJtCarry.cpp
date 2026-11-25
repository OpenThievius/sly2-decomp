#include "sly2.h"
#include "jt.h"
extern "C" {
void FadeAloIn(void *, float);
QW PosLoWorld(void *);
void CarryThrow_UpdateArc(void *, int);
void CarryThrow_SetState(void *, int);
}
/* the carry state InitJt starts at 0x11B0 (JT::PvCarry): the carried object and the position it was lifted from */
struct JTCARRYVIEW {
    u8 unknown_0x0[0x11C0];
    void *palo; /* CARRYTHROW::pso, the part's carried object */
    u8 unknown_0x11C4[0xCC];
    QW pos;
};
void StartJtCarry(JT *jt, void *palo, void *ploFrom)
{
    JTCARRYVIEW *view = (JTCARRYVIEW *)jt;
    FadeAloIn(palo, 0.25f);
    view->palo = palo;
    view->pos = PosLoWorld(ploFrom);
    CarryThrow_UpdateArc(jt->PvCarry(), 0);
    jt->SetMode(7);
    CarryThrow_SetState(jt->PvCarry(), 7);
}
