// SPDX-License-Identifier: GPL-3.0-or-later
struct Clock { float time; float dt; };
#include "sly.h"
struct ATTACH { SLY *pjt; float t; int kind; char pad[0x14 - 0xC]; int ptarget; int pmember; char pad2[0x4C4 - 0x1C]; int carryTarget; char pad3[0x500 - 0x4C8]; int noHold; };
extern Clock g_2dded0;
extern "C" void SetAttachSubstate(ATTACH *, int);
extern "C" void SetJtJtcs(SLY *, int);
extern "C" void EnsureAloSfx__FP3ALO(SLY *);
extern "C" void ForgetJtGuards(ATTACH *);
extern "C" void Carry_SetState(void *, int);
extern "C" void StartAttach(ATTACH *pattach, unsigned kind, int ptarget, int pmember)
{
    int sub;
    SetAttachSubstate(pattach, -1);
    pattach->kind = kind;
    pattach->t = g_2dded0.time;
    pattach->pmember = pmember;
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
        jt->field_0x1854 = ptarget;
        SetJtJtcs(jt, 0);
        EnsureAloSfx__FP3ALO(jt);
        break;
    }
    case 5:
    case 9:
        pattach->carryTarget = pattach->ptarget;
        Carry_SetState((char *)pattach + 0x440, 0);
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
