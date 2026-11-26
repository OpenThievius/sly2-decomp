// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct B12 { int w[3]; };
struct KEYB { float pos[3]; float t; QW in; QW out; };
struct ACRB { u8 unknown_0x0[8]; KEYB *akey; };
extern "C" int IkeyFindAcrb(ACRB *, float);
extern "C" void EvaluateBezierPos__FfffP6VECTORN63(float, float, float, QW, QW, QW, QW, QW *, QW *, QW *);
extern "C" void EvaluateAcrb(ACRB *pacrb, float t, float svt, QW *pvecPos, QW *pvecVel)
{
    QW posPrev;
    QW posNext;
    int ikey = IkeyFindAcrb(pacrb, t);
    /* the key as an address: as a typed pointer the previous key's address is shared and the loads move (scores 10, 20) */
    int pkey = ikey * 0x30 + (sptr)pacrb->akey;
    *(B12 *)&posPrev = *(B12 *)(pkey - 0x30);
    *(B12 *)&posNext = *(B12 *)pkey;
    float tPrev = ((KEYB *)(pkey - 0x30))->t;
    EvaluateBezierPos__FfffP6VECTORN63(((KEYB *)pkey)->t - tPrev, t - tPrev, svt, posPrev, ((KEYB *)pkey)[-1].out, posNext, ((KEYB *)pkey)->in, pvecPos, pvecVel, 0);
}
