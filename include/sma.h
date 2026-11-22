/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SMA, an animation driven by a state machine (retail's name, from SetSmaGoal__FP3SMA3OID): only the words two readers agree on.
   C and C++. */
#ifndef SLY2_SMA_H
#define SLY2_SMA_H
#include "types.h"

struct SM;
struct ASEGA;

struct SMA {
    u8 unknown_0x0[0x24];
    /* 0x24 */ struct SM *psm;       /* SetSmaGoalIfReachable (IsmsFindSmOptional, PsmtChooseSmTowards), func_001D14C0 (the goal it snaps to) */
    u8 unknown_0x28[0x8];
    /* 0x30 */ struct ASEGA *pasega; /* SetSmaGoalIfReachable tests it; RenderDprizeAll asks PchnFindAseg for it */
};
#endif
