// SPDX-License-Identifier: GPL-3.0-or-later
#include "tn.h"
#include "sw.h"
extern "C" {
struct PMF8 { u64 value; } __attribute__((packed)); /* a pointer to member function: 8 bytes, read whole (CancelSwCallbacks's PMF) */
void CancelSwCallbacks(SW *, u32, TN *, u64, s32);
void RemoveLoHierarchy(LO *);
extern SW B_003DD490;
extern const PMF8 RO_002A96E8;
void RemoveTn(TN *tn) {
    RemoveLoHierarchy(tn);
    CancelSwCallbacks(&B_003DD490, 1, tn, RO_002A96E8.value, 0);
}
}
