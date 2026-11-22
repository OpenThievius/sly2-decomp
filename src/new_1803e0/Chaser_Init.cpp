// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"
extern "C" void func_0017F090(CHASER *);
extern "C" void func_001813C0(CHASER *, float);
extern "C" void func_001813F0(CHASER *, float);
extern "C" void func_0017F3E0(CHASER *, int, ANIMENTRY *);
extern "C" void Chaser_Init(CHASER *pchaser)
{
    func_0017F090(pchaser);
    float one = 1.0f;
    pchaser->field_0x340 = one;
    pchaser->field_0x350 = one;
    pchaser->field_0x364 = one;
    pchaser->field_0x338 = 250.0f;
    pchaser->field_0x370 = -3.402823466e+38f;
    pchaser->field_0x374 = 3.402823466e+38f;
    func_001813C0(pchaser, one);
    func_001813F0(pchaser, one);
    func_0017F3E0(pchaser, 5, pchaser->aentry);
    pchaser->state = -1;
}
