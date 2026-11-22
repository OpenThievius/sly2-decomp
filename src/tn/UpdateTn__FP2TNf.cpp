// SPDX-License-Identifier: GPL-3.0-or-later
#include "tn.h"
#include "sw.h"
extern "C" {
struct PMF8 { u64 value; } __attribute__((packed)); /* a pointer to member function: 8 bytes, read whole (CancelSwCallbacks's PMF) */

void QueueSwCallback(SW *, TN *, u64, s32);
void UpdateLo(LO *);
extern SW B_003DD490;
extern const PMF8 RO_002A96F0;
void UpdateTn__FP2TNf(TN *tn) {
    UpdateLo(tn);
    if (tn->tnsOverride != 0) {
        QueueSwCallback(&B_003DD490, tn, RO_002A96F0.value, 0);
    }
}
}
