/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GOALPATROL: a guard goal that walks a path of nodes and watches for notices (it sets the guard's goals 0x9E watch, 0xA7 follow the
   curve, 0xAC jump, 0xA4 react). Its functions sit at 0x14A178 to 0x14AE38 (Init func_0014A1B0, Activate func_0014A200, Deactivate
   func_0014A248, Update func_0014A2A0, SetState func_0014AE38). Same form as goalpost.h's GOALPOSTWATCH, whose NOTICE it uses. C and C++ (GOAL_CLASS: goals.h) */
#ifndef SLY2_GOALPATROL_H
#define SLY2_GOALPATROL_H
#include "goalpost.h"

/* one node of a path, 12 bytes: func_0014AD70 reads its kind, func_0014AE18 its object */
struct PATHNODE {
    s32 kind;
    u8 unknown_0x4[0x4];
    /* 0x8 */ struct LO *plo; /* the object the guard walks to: func_0014AE18 returns it, func_0014AE38 turns to its position */
};

/* a path (the object PostLoLoad is run on by func_0014A0A8): its node array at 0x58 */
struct PATH {
    u8 unknown_0x0[0x58];
    /* 0x58 */ struct PATHNODE *anode; /* func_0014AD70, func_0014AE18 */
};

#define GOALPATROL_FIELDS \
    /* 0x30 */ s32 state;       /* func_0014A1B0 writes -1; SetState, Update */ \
    /* 0x34 */ f32 tState;      /* SetState */ \
    /* 0x38 */ struct PATH *ppath; /* func_0014AD70, func_0014AE18 */ \
    /* 0x3C */ s32 inodeCur;    /* func_0014A1B0 writes -1; func_0014AD70, func_0014AE18, Update compares it with inodeTarget */ \
    /* 0x40 */ s32 inodeTarget; /* func_0014A1B0 writes -1; func_0014AD70, Update stores func_0014AA30's result */ \
    /* 0x44 */ struct NOTICE *pnotice; /* Update stores PsenseFindNotice's result; SetState (state 3) hands it to GoalReact and reads its delay range */ \
    /* 0x48 */ f32 tActivate;   /* Activate stores the clock */
GOAL_CLASS(GOALPATROL, GOAL, GOALPATROL_FIELDS)
#endif
