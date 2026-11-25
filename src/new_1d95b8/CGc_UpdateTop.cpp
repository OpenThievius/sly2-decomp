#include "sly2.h"
/* A screen of the controller's list (CGC): vtable pointer at 0xC, the controller block it reads at 0x10. Slot 9 is the focus
   change (CGc_UpdateTop calls it with 0 when the screen loses the top and 1 when it gains it, and the screen it replaces). */
struct SCRBASE {
    u8 unknown_0x0[0xC];
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void SetFocus(int fFocus, struct SCR *pscrOther); /* 9: CGc_UpdateTop */
};
struct SCR : SCRBASE {
    /* 0x10 */ void *pjoy;
};
struct CGC { SCR *pnew; u8 unknown_0x4[8]; SCR *ptop; };
extern char B_002DFC00;
void CGc_UpdateTop(CGC *g)
{
    SCR *pnew = g->pnew;
    if (pnew == g->ptop)
        return;
    if (g->ptop) {
        g->ptop->pjoy = 0;
        g->ptop->SetFocus(0, pnew);
    }
    SCR *pold = g->ptop;
    g->ptop = pnew;
    if (pnew) {
        pnew->pjoy = &B_002DFC00;
        pnew->SetFocus(1, pold);
    }
}
