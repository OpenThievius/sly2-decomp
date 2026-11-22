/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RSMG, a rule state machine record, 0x10 bytes: the root object, the state machine animation under it, and the goals it is sent to on
   trigger and on untrigger. FAddRsmg fills them (pzo_hide.h's GRAB keeps an array), TriggerRsmg steps an array of them, TriggerRsmgEntry
   reads one. C and C++. */
#ifndef SLY2_RSMG_H
#define SLY2_RSMG_H
#include "types.h"

struct RSMG {
    /* 0x0 */ s32 oidRoot;
    /* 0x4 */ s32 oidSM;
    /* 0x8 */ s32 oidTriggerGoal;
    /* 0xC */ s32 oidUntriggerGoal;
};
#endif
