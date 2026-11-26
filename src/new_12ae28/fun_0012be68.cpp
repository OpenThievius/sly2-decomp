// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct B12 { int w[3]; };
struct KEYBL { float pos[3]; float t; QW tan; };
struct ACRBL { u8 unknown_0x0[8]; KEYBL *akey; };
extern "C" int func_0012BB70(ACRBL *, float);
extern "C" void EvaluateBezierPos__FfffP6VECTORN63(float, float, float, QW, QW, QW, QW, QW *, QW *, QW *);
extern "C" void func_0012BE68(ACRBL *pacrbl, float t, float svt, QW *pvecPos, QW *pvecVel)
{
    QW posPrev;
    QW posNext;
    int ikey = func_0012BB70(pacrbl, t);
    /* the key as an address: as a typed pointer the previous key's address is shared and the loads move (scores 10, 20) */
    int pkey = ikey * 0x20 + (sptr)pacrbl->akey;
    *(B12 *)&posPrev = *(B12 *)(pkey - 0x20);
    *(B12 *)&posNext = *(B12 *)pkey;
    float tPrev = ((KEYBL *)(pkey - 0x20))->t;
    EvaluateBezierPos__FfffP6VECTORN63(((KEYBL *)pkey)->t - tPrev, t - tPrev, svt, posPrev, ((KEYBL *)pkey)[-1].tan, posNext, ((KEYBL *)pkey)->tan, pvecPos, pvecVel, 0);
}
