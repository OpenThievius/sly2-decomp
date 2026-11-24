/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GOAL, one step of an actor's behaviour: class 155 of retail's class table, 0x30 bytes, derived from the root BASIC
   (include/lo.h), the other branch beside LO. Its vtable (0x2D9480) adds slots 7 to 14; about fifty classes derive from it
   (156 GoalBrain, 157 GoalAnim, 160 GoalHit and others, 0x30 to 0xE0 bytes). The slots are named after what the subclasses put
   there (GoalBrain_Init, GoalHit_Activate, Goal_Deactivate, GoalBrain_Update, Goal_FHandleMessage, Goal_FillVjoy). A field here
   is read or set by one of GOAL's own methods or by two other readers that agree. C++ only. */
#ifndef SLY2_GOAL_H
#define SLY2_GOAL_H
#include "lo.h"

struct STEP;
struct JOY;

/* a node of the list a goal counts itself into while it is active: its link at 0x14 and the count at 0x20 */
struct GOALLINK {
    u8 unknown_0x0[0x14];
    /* 0x14 */ struct GOALLINK *next;
    u8 unknown_0x18[0x8];
    /* 0x20 */ s32 count;                /* func_001EEFC0 adds 1 to it, func_001EF038 subtracts 1 */
};

struct GOAL : BASIC {
    virtual void Init();                /*  7: func_001EEF68 (empty); GoalBrain_Init */
    virtual void Activate();            /*  8: func_001EEF70 (empty); GoalBrain_Activate, GoalHit_Activate */
    virtual void Deactivate();          /*  9: Goal_Deactivate */
    virtual void Update();              /* 10: func_001EEF98 (empty); GoalBrain_Update, GoalHit_Update */
    virtual void Slot11();              /* 11: func_001EEFB8 (empty) */
    virtual void Slot12();              /* 12: func_001EEFA0 */
    virtual int FHandleMessage(int arg1, int arg2);      /* 13: Goal_FHandleMessage; GoalStack_HandleMessage calls it with two ints */
    virtual void FillVjoy(struct JOY *pjoy); /* 14: Goal_FillVjoy; UpdateJt calls the top goal's with the player's controller */
    /* 0x10 */ struct STEP *pstep;      /* the actor: Goal_FillVjoy (14) reads its heading (STEP 0x1A8), func_001EEFA0 (12) its 0x204 */
    /* 0x14 */ struct GOALLINK *plink; /* the list func_001EEFC0 and func_001EF038 walk (two readers that agree) */
    /* 0x18 */ struct GOAL *pgoalChild; /* Goal_Deactivate (9) pops it; GoalGotoPos_SetPos and others read it */
    /* 0x1C */ s32 fActive;             /* func_001EEFC0 sets it (once), func_001EF038 clears it */
    u8 unknown_0x20[0x10];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(GOAL, 0x30);
SLY2_OFFSET_CHECK(GOAL, pstep, 0x10);
SLY2_OFFSET_CHECK(GOAL, pgoalChild, 0x18);
#endif
#endif
