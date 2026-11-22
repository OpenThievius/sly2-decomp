// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"
#include "sw.h"
extern "C" {
struct PMF8 { u64 value; } __attribute__((packed)); /* a pointer to member function: 8 bytes, read whole (CancelSwCallbacks's PMF) */
void CancelSwCallbacks(SW *psw, u32 grf, SOHIT *pso, u64 pmf, int nArg);
extern SW B_003DD490;
extern const PMF8 RO_002A5638;
void func_0017F6B0(SOHIT *pso) {
    pso->hp = pso->hpMax;
    if (pso->fTouchQueued != 0) {
        CancelSwCallbacks(&B_003DD490, 1, pso, RO_002A5638.value, 0);
    }
}
}
