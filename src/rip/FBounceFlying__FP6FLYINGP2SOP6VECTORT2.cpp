// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct VECTOR;
struct ALO; struct RIP;
struct SO;
struct BOUNCEHIT { char *pso; char *basic; };
struct FLYING { u8 unknown_0x0[0xF0]; ALO *alo; };
extern "C" int FIsBasicDerivedFrom(void *basic, int cid);
extern "C" void RemoveRip(RIP *rip);
extern "C" void CreateStuck__FP3RIPP3ALOP2SOP6VECTORT3PP5STUCK(RIP *, ALO *, SO *, QW, QW);
extern int D_002C1F70[];

int FBounceFlying__FP6FLYINGP2SOP6VECTORT2(FLYING *flying, BOUNCEHIT *so, QW pos, QW normal)
{
    for (unsigned index = 0; index < 1; index++) {
        if (FIsBasicDerivedFrom(so->basic, D_002C1F70[index]))
            return 0;
    }
    if (!FIsBasicDerivedFrom(so->basic, 0x59))
        CreateStuck__FP3RIPP3ALOP2SOP6VECTORT3PP5STUCK((RIP *)flying, flying->alo, (SO *)so->pso, pos, normal);
    RemoveRip((RIP *)flying);
    return 1;
}
