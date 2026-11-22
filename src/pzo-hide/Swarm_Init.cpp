// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void func_0017F090(SWARM *);
extern "C" void InitDl__FP2DLi(DL *, int);

extern "C" void Swarm_Init(SWARM *swarm)
{
    func_0017F090(swarm);
    if (!(swarm->grfSw & 1))
        swarm->pgrfentry->grf |= 8;
    else
        swarm->grfSw |= 8;
    InitDl__FP2DLi(&swarm->dlDead, 0x60);
}
