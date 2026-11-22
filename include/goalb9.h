/* SPDX-License-Identifier: GPL-3.0-or-later */
/* 0xB9 (185), no recovered name: the goal that runs the guard's sgs 0x27 (a GoalB8 beside it keeps the same four fields).
   Init func_0017CE68, Activate func_0017CEA0, Deactivate func_0017CED0, SetState func_0017D058, func_0017D110 (turns it toward
   the guard's path end). Layout from those methods; the size is not measured. */
#ifndef SLY2_GOALB9_H
#define SLY2_GOALB9_H
#include "goals.h"

#define GOALB9_FIELDS \
    /* 0x30 */ s32 state;           /* func_0017CE68 writes -1; func_0017D058 (SetState) */ \
    /* 0x34 */ f32 tState;          /* func_0017D058: the clock at the last state change */ \
    /* 0x38 */ f32 sCrv;            /* func_0017D110 stores SMaxCrv or SMinCrv of the guard's path here */ \
    /* 0x3C */ s32 field_0x3C;      /* func_0017D058 clears it in state 1 */
GOAL_CLASS(GOALB9, GOAL, GOALB9_FIELDS)
#endif
