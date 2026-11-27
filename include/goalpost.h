/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The guard-post goals of crv-lo (config/recovered/decomp_names.md: GoalPostRun_* 0x155560 to 0x155788, GoalPostWatch_* 0x1559B0 to
   0x155D90) and the guard's post table. A post pair is one of 32 entries of 0x24 bytes that LoadGuardPosts allocates at guard +0x1014:
   two posts, each with the zone volume that says when the target is on its side. Same form as goals.h: one definition for C and C++
   (C gets the flat layout). Readers are listed per field. */
#ifndef SLY2_GOALPOST_H
#define SLY2_GOALPOST_H
#ifdef __cplusplus
#include "stepguard.h"
#endif
#include "goals.h"

struct POSTPAIR {
    /* 0x00 */ s32 oidA;            /* AddGuardPost stores it, PostLoadGuardPosts looks it up into ploA (two readers agree) */
    /* 0x04 */ struct LO *ploA;     /* PloPostSide (func_00155A68) returns it when the target is in volume A; PostLoadGuardPosts sets it */
    /* 0x08 */ s32 oidVolumeA;      /* AddGuardPost, PostLoadGuardPosts (into pvolumeA) */
    /* 0x0C */ struct LO *pvolumeA; /* PloPostSide: the zone it tests the target against; PostLoadGuardPosts sets it */
    /* 0x10 */ s32 oidB;            /* AddGuardPost, PostLoadGuardPosts (into ploB) */
    /* 0x14 */ struct LO *ploB;     /* PloPostSide returns it otherwise; PostLoadGuardPosts sets it */
    /* 0x18 */ s32 oidVolumeB;      /* AddGuardPost, PostLoadGuardPosts (into pvolumeB) */
    /* 0x1C */ struct LO *pvolumeB; /* PloPostSide; PostLoadGuardPosts sets it */
    /* 0x20 */ s32 used;            /* GoalPostRun_SetState sets it when the run leaves state 0 */
};

/* GoalPostRun (state 0 pushes goal 0xB5, state 1 GoalNotice 0xA5): runs to a post. Init GoalPostRun_Init (func_00155560). */
#define GOALPOSTRUN_FIELDS \
    /* 0x30 */ s32 state;           /* SetState (-1 before the first); Activate, Deactivate, Update */ \
    /* 0x34 */ f32 tState;          /* SetState */ \
    /* 0x38 */ struct LO *ptarget;  /* Activate hands it to func_00208540; SetState gives it to goal 0xA5 */ \
    /* 0x3C */ struct POSTPAIR *ppost; /* Activate stores PpostPick's result; SetState gives it to goal 0xB5 and marks it used */
GOAL_CLASS(GOALPOSTRUN, GOAL, GOALPOSTRUN_FIELDS)

/* GoalPostWatch: the guard turns to the post, watches, walks the two-point path, reacts to a notice. Init func_001559B0. */
#define GOALPOSTWATCH_FIELDS \
    /* 0x30 */ s32 state;           /* Init sets -1; SetState, Update */ \
    /* 0x34 */ f32 tState;          /* SetState; Update */ \
    /* 0x38 */ struct POSTPAIR *ppost; /* PloPostSide reads its zones; Update */ \
    /* 0x3C */ f32 tLimit;          /* Init and SetState (state 0) set FLT_MAX */ \
    /* 0x40 */ struct LO *ploPost;  /* SetState (state 0) stores PloPostSide's result; Update walks to it */ \
    /* 0x44 */ f32 tReact;          /* Update */ \
    /* 0x48 */ f32 tAnim;           /* Update */ \
    /* 0x4C */ struct LO *ploTarget; /* the object watched: PloPostSide, SetState, Update (PsenseFindNotice) */ \
    /* 0x50 */ s32 cReact;          /* SetState (state 3) counts reactions */ \
    /* 0x54 */ struct NOTICE *pnotice; /* SetState reads its delay range; Update stores PsenseFindNotice's result */
GOAL_CLASS(GOALPOSTWATCH, GOAL, GOALPOSTWATCH_FIELDS)

/* what PsenseFindNotice returns: SetState (state 3) draws the next delay between low and high */
struct NOTICE {
    u8 unknown_0x0[0x60];
    /* 0x60 */ f32 low;
    /* 0x64 */ f32 high;
};

#ifdef __cplusplus
/* The guard with a post table: class 59 of retail's class table (0x1020 bytes, factory 0x111828, derived from class 58). Its own
   methods: LoadGuardPosts (func_001553F0, slot 14) and PostLoadGuardPosts (slot 15); GoalBrain_ChooseNextCommand tests class 59
   and its post count. */
struct STEPGUARDPOSTS : STEPGUARD {
    /* 0x1010 */ s32 cpost;         /* AddGuardPost counts it up, PostLoadGuardPosts (15) walks it, GoalBrain_ChooseNextCommand tests it */
    /* 0x1014 */ struct POSTPAIR *apost; /* LoadGuardPosts (14) allocates it; AddGuardPost, PostLoadGuardPosts */
    /* 0x1018 */ s32 tickPick;      /* LoadGuardPosts (14), GoalPostRun_SetState, GoalPostRun_Activate */
    u8 unknown_0x101C[0x4];
};
#if defined(__mips__)
SLY2_SIZE_CHECK(STEPGUARDPOSTS, 0x1020);
SLY2_OFFSET_CHECK(STEPGUARDPOSTS, cpost, 0x1010);
SLY2_OFFSET_CHECK(STEPGUARDPOSTS, apost, 0x1014);
#endif
#endif
#endif
