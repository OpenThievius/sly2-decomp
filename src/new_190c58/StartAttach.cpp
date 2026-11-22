// SPDX-License-Identifier: GPL-3.0-or-later
#include "attach.h"
#include "clock.h"
extern "C" void SetAttachSubstate(ATTACH *, int);
extern "C" void SetJtJtcs(SLY *, int);
extern "C" void EnsureAloSfx__FP3ALO(SLY *);
extern "C" void Carry_SetState(u8 *pcarry, int);
extern "C" void StartAttach(ATTACH *pattach, unsigned kind, LO *ptarget, s32 imember)
{
    int sub;
    SetAttachSubstate(pattach, -1);
    pattach->kind = kind;
    pattach->t = g_2dded0.t;
    pattach->imember = imember;
    pattach->ptarget = ptarget;
    SLY *pjt = pattach->pjt;
    pjt->SetMode(2);
    switch (kind) {
    case 0:
    case 13:
        sub = 5;
        break;
    case 6: {
        SLY *jt = pattach->pjt;
        sub = 0;
        jt->field_0x1854 = (sptr)ptarget;
        SetJtJtcs(jt, 0);
        EnsureAloSfx__FP3ALO(jt);
        break;
    }
    case 5:
    case 9:
        pattach->carryTarget = pattach->ptarget;
        Carry_SetState(pattach->carry, 0);
        sub = 0;
        break;
    case 8:
        sub = 7;
        goto forget;
    case 1:
        sub = 0;
    forget:
        ForgetJtGuards(pattach);
        break;
    case 11:
    case 12:
        sub = 0;
        pattach->noHold = 1;
        break;
    default:
        sub = 0;
        break;
    }
    SetAttachSubstate(pattach, sub);
}
