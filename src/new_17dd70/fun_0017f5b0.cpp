// SPDX-License-Identifier: GPL-3.0-or-later
#include "sohit.h"
#include "sw.h"
extern "C" {
struct PMF8 { u64 value; } __attribute__((packed)); /* a pointer to member function: 8 bytes, read whole (CancelSwCallbacks's PMF) */
void QueueSwCallback(SW *psw, SOHIT *pso, u64 pmf, void *pother);
extern SW B_003DD490;
extern const PMF8 RO_002A5630;
void func_0017F5B0(SOHIT *pso, void *pother) {
    if (pso->fTouchQueued == 0) {
        u64 pmf = RO_002A5630.value;
        pso->fTouchQueued = 1;
        QueueSwCallback(&B_003DD490, pso, pmf, pother);
    }
}
}
