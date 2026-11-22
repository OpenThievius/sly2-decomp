/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The goals of a guard and of the player's partners: the subclasses of GOAL (include/goal.h, class 155, 0x30 bytes) that a goal
   stack holds (a guard's, or a JT's: GoalFollowCrvVjoy and the partner goals at the end), and the records they share (GOALSTACK, GOALTARGET, ROUTE, the brain's GOALCMD). One definition for C and C++: in C++ each class derives
   from its parent (GOAL, or GOALANIM, GOALHIT, GOALFOLLOWCRV); in C (goal.h is C++ only) the same layout is written flat, the
   parents' fields repeated through their *_FIELDS macros after GOAL_FIELDS, GOAL's 0x30 bytes.

   Each class is identified by its class id in retail's class table (0x2BAAE8, config/recovered/class_diff.tsv): the id is what
   func_00205438 and GoalStack_PgoalFind take, and the class's vtable names its methods (slot 7 Init, 8 Activate, 9 Deactivate,
   10 Update, 13 FHandleMessage). The table also gives the parent and the size. Class names follow the recovered names of the
   methods (config/recovered/decomp_names.md) where there are some, else the class id. A field is listed with its readers: a
   method of the class (certain), or two functions that agree, or a function that gets the goal by class id (certain). */
#ifndef SLY2_GOALS_H
#define SLY2_GOALS_H
#include "types.h"
#include "guard.h"
#ifdef __cplusplus
#include "goal.h"
#endif

struct LO;
struct SO;
struct XF;
struct STEP;
struct STEPGUARD;
struct CRV;
struct PIPE;
struct PZLINK;
struct JOY;

/* The actor of a guard's goal: every goal here belongs to a STEPGUARD */
#define GOAL_GUARD(goal) ((struct STEPGUARD *)(goal)->pstep)
/* The actor of a player's goal (GoalFollowCrvVjoy, the partner goals): a JT (jt.h; in C its view JTVIEW, jtview.h) */
#ifdef __cplusplus
#define GOAL_JT(goal) ((struct JT *)(goal)->pstep)
#else
#define GOAL_JT(goal) ((struct JTVIEW *)(goal)->pstep)
#endif

/* The goal stack, embedded in STEP at 0x26C (STEP::pgoalstack()): GoalStack_Push, GoalStack_PgoalFind, GoalStack_Clear */
struct GOALSTACK {
    u8 unknown_0x0[0x4];
    /* 0x4 */ s32 count;                /* GoalStack_PgoalFind loops over it, GoalStack_Clear tests it */
    /* 0x8 */ struct GOAL *apgoal[0];   /* GoalStack_PgoalFind, GoalStack_Clear (the first) */
};

/* A place a goal goes to or stands at, 0x20 bytes: func_001C1EC0 resolves it to a position (the curve's closest point to a given
   position, else the object's world position, else pos); func_002562A8 initializes one, SetGoalTarget hands one to a goal. */
struct GOALTARGET {
    /* 0x0 */ void *pcrv;   /* func_001C1EC0 (the curve it searches, when set); func_0017D8A8 clears it */
    /* 0x4 */ void *plo;    /* func_001C1EC0 (its object's world position, when no curve) */
    u8 unknown_0x8[0x8];
    /* 0x10 */ QW pos;      /* func_001C1EC0 (a fixed position); SetSearchState, func_0017C928 fill it */
};

/* The route a GoalFollowRoute walks: SetState (kind, waypoints), NextWaypoint (the count) */
struct ROUTE {
    u8 unknown_0x0[0x50];
    /* 0x50 */ s32 cwaypoint;              /* NextWaypoint: the goal ends when its index reaches it */
    u8 unknown_0x54[0xC];
    /* 0x60 */ struct GOALTARGET awaypoint[6]; /* GoalFollowRoute_SetState indexes it by the goal's index; 6 is only the room up to kind */
    /* 0x120 */ s32 kind;                  /* GoalFollowRoute_SetState: 0 walks a two-point curve, 1 goes to the waypoint */
};

/* a quadword read whole or by lanes */
union VECTORQW { QW q; f32 f[4]; };

/* A command of the brain (0x70 bytes): GoalBrain_SetCommand switches on its type and copies its arguments to the goal it starts */
struct GOALCMDARGS {
    /* 0x0 */ s32 arg;              /* the command's object or id */
    /* 0x4 */ f32 argf;             /* command 18 */
    u8 unknown_0x8[0x4];
    /* 0xC */ u32 grfHit;           /* as GOALHIT::args: GoalHit_Activate tests 0x40000, func_001796D0 picks the animation from it */
    u8 unknown_0x10[0x20];
    /* 0x30 */ union VECTORQW vecVelocity; /* as GOALHIT::args: GoalHit_Activate (its xy heading and length) */
    u8 unknown_0x40[0x20];
} __attribute__((aligned(16)));    /* the 0x60 bytes are copied whole to the goal of commands 9, 10 and 11 */

struct GOALCMD {
    /* 0x0 */ s32 type;             /* GoalBrain_SetCommand switches on it (0 to 19), GoalBrain_Update; func_0020A540 */
    u8 unknown_0x4[0xC];
    /* 0x10 */ struct GOALCMDARGS args;
} __attribute__((aligned(16)));

#ifdef __cplusplus
#define GOAL_FIELDS
#else
/* C: GOAL's 0x30 bytes (include/goal.h). pstep is GOAL's STEP; a guard goal's actor is a STEPGUARD, so C names it that. */
#define GOAL_FIELDS \
    u8 unknown_0x0[0x10]; \
    /* 0x10 */ struct STEPGUARD *pstep; \
    u8 unknown_0x14[0x4]; \
    /* 0x18 */ struct GOAL *pgoalChild; \
    u8 unknown_0x1C[0x14];
struct GOAL { GOAL_FIELDS };
#endif

/* Each class: its fields as a macro (for the C flat form and the C forms of its subclasses), then the class. */
#ifdef __cplusplus
#define GOAL_CLASS(name, base, fields) struct name : base { fields };
#else
#define GOAL_CLASS(name, base, fields) struct name { base##_C fields };
#define GOAL_C GOAL_FIELDS
#endif

/* 0x9C (156) GoalBrain, 0xB0 bytes: GoalBrain_Init, GoalBrain_Activate, GoalBrain_Update, GoalBrain_SetCommand (GoalBrain_*). The goal
   it runs sits in pgoalChild. */
#define GOALBRAIN_FIELDS \
    /* 0x30 */ struct GOALCMD cmd;  /* the current command: GoalBrain_SetCommand, GoalBrain_Update; func_0020A540 reads its type */ \
    /* 0xA0 */ f32 tCommand;        /* GoalBrain_SetCommand: when it was set */ \
    /* 0xA4 */ f32 tRetry;          /* GoalBrain_SetCommand (command 17), GoalBrain_Update */
GOAL_CLASS(GOALBRAIN, GOAL, GOALBRAIN_FIELDS)

/* 0x9D (157) GoalAnim, 0x50 bytes: Init func_00174920, Activate func_00174950, Deactivate func_00174B28, GoalAnim_Update,
   GoalAnim_FHandleMessage, GoalAnim_SetState, FGoalAnimDone. The parent of the animation goals below. */
#define GOALANIM_FIELDS \
    /* 0x30 */ s32 state;           /* GoalAnim_SetState; FGoalAnimDone (state 1) */ \
    /* 0x34 */ f32 tState;          /* GoalAnim_SetState */ \
    /* 0x38 */ struct LO *ptarget;  /* what it looks at: func_00175258 reads its position, func_00175090 tests it; the brain's commands
                                       3, 13, 14, 17 and GoalReact, GoalStand, GoalFollowCrvAnim, GoalFlee set it */ \
    /* 0x3C */ s32 sgs;             /* func_00174950 adds it to the guard's sgs, func_00174B28 removes it; each Init sets its own */ \
    /* 0x40 */ struct ANIMREF *panimref; /* func_00174950 takes PguardanimCurrent's entry when it is 0; func_001796D0 points it into
                                            the guard's aarefB; GoalAnim_Update */ \
    u8 unknown_0x44[0xC];
GOAL_CLASS(GOALANIM, GOAL, GOALANIM_FIELDS)
#ifndef __cplusplus
#define GOALANIM_C GOAL_FIELDS GOALANIM_FIELDS
#endif

/* 0x9F (159) a GoalAnim that steers its jump animation's JUMPER at the target, 0x60 bytes: Init func_001751C0, Activate func_001751F0,
   Update func_00175258, Deactivate func_001752C0, FHandleMessage func_001752F0; func_00174EA0 (slot 12 of GoalAnim) reads its jumper */
#define GOALTRACK_FIELDS \
    /* 0x50 */ s32 fTrackTarget;    /* func_00175258 clears it without a jumper, func_001751F0 sets it for a kind-2 animref */ \
    u8 unknown_0x54[0xC];
GOAL_CLASS(GOALTRACK, GOALANIM, GOALTRACK_FIELDS)

/* 0xA0 (160) GoalHit, 0xC0 bytes: GoalHit_Activate, GoalHit_Deactivate, GoalHit_Update; 0xA1, 0xA2, 0xA3 derive from it (Init
   func_001796A0, func_00179750, func_00179868; the brain's commands 9, 10 and 11 copy their arguments into args) */
#define GOALHIT_FIELDS \
    /* 0x50 */ struct GOALCMDARGS args; /* the command's arguments: arg is the object that hit (GoalHit_Activate, func_001796D0; func_00208E70
                                           reads it as the object 0xA1 and 0xA2 hold), grfHit, vecVelocity */ \
    /* 0xB0 */ f32 tJolt;           /* GoalHit_Activate sets it 0.05 after a rumble; GoalHit_Update jolts the camera when it passes */ \
    /* 0xB4 */ f32 tLimit;          /* GoalHit_Activate; GoalHit_Update calls func_001F7A68 when it passes */ \
    u8 unknown_0xB8[0x8];
GOAL_CLASS(GOALHIT, GOALANIM, GOALHIT_FIELDS)

/* 0xA4 (164) GoalReact, 0x50 bytes: Init func_001753D8, Activate func_00175410, Deactivate func_00175448, Update func_00175600,
   FHandleMessage func_001756C0, SetState func_00175488, FGoalReactDone */
#define GOALREACT_FIELDS \
    /* 0x30 */ struct LO *ptarget;  /* func_00175488 subscribes to it; func_001756C0 compares the message's object with it */ \
    /* 0x34 */ s32 state;           /* func_00175488, FGoalReactDone */ \
    /* 0x38 */ f32 tState;          /* func_00175488 */ \
    /* 0x3C */ struct XF *pxf;      /* func_00175488: the aim transform it hands to func_0020AC28 (it tests its pxfParent) */ \
    /* 0x40 */ s32 fHit;            /* func_001756C0 sets it on message 0xB from the guard */ \
    u8 unknown_0x44[0xC];
GOAL_CLASS(GOALREACT, GOAL, GOALREACT_FIELDS)

/* 0xA5 (165) GoalNotice, 0x60 bytes: Init func_00175758, Activate func_00175790, Deactivate func_001757D0, GoalNotice_Update,
   GoalNotice_SetState, FGoalNoticeDone. The brain's command 4 and GoalPicked start it (turn to an object). */
#define GOALNOTICE_FIELDS \
    /* 0x30 */ struct LO *ptarget;  /* func_00175790 hands it to func_00208540 (the guard's alert object); GoalBrain_SetCommand,
                                       func_0017B8B0 set it */ \
    /* 0x34 */ s32 state;           /* GoalNotice_SetState, FGoalNoticeDone */ \
    u8 unknown_0x38[0x8]; \
    /* 0x40 */ s32 field_0x40;      /* func_0017B8B0 sets 1 */ \
    u8 unknown_0x44[0x1C];
GOAL_CLASS(GOALNOTICE, GOAL, GOALNOTICE_FIELDS)

/* 0xA6 (166) GoalFollowCrv, 0xC0 bytes: GoalFollowCrv_Init, _Activate, _Update, _SetState (slot 15), _SetCrv, _FBlocked; 0xA7 and
   0xA8 derive from it */
#define GOALFOLLOWCRV_FIELDS \
    /* 0x30 */ struct CRV *pcrv;    /* GoalFollowCrv_SetCrv */ \
    /* 0x34 */ f32 s;               /* the position on the curve: GoalFollowCrv_SetCrv */ \
    /* 0x38 */ s32 reverse;         /* GoalFollowCrv_SetCrv */ \
    /* 0x3C */ s32 open;            /* GoalFollowCrv_SetCrv: 1 when the curve is not closed */ \
    /* 0x40 */ s32 field_0x40;      /* GoalFollowRoute_SetState sets 1 before SetCrv */ \
    /* 0x44 */ f32 sEnd;            /* GoalFollowCrv_SetCrv: the end of an open curve, in the direction of travel */ \
    /* 0x48 */ f32 sHint;           /* GoalFollowCrv_SetCrv: where to start looking, or -1 */ \
    /* 0x4C */ s32 state;           /* GoalFollowCrv_SetState, GoalFollowCrv_FBlocked (3), GoalFollowCrvAnim_SetState */ \
    /* 0x50 */ f32 tState;          /* GoalFollowCrv_SetState */ \
    u8 unknown_0x54[0x10]; \
    /* 0x64 */ f32 field_0x64;      /* GoalFollowRoute_SetState sets 10.0 */ \
    u8 unknown_0x68[0x18]; \
    /* 0x80 */ QW posGoal;          /* the point it steers at: GoalFollowCrv_Activate, GoalFollowCrv_Update; GoalFollowCrvVjoy's Activate and
                                       Update hand it to func_001448F0 */ \
    u8 unknown_0x90[0x20]; \
    /* 0xB0 */ QW posEnd;           /* GoalFollowCrv_SetCrv: GetPathPosFromS writes the end's position */
GOAL_CLASS(GOALFOLLOWCRV, GOAL, GOALFOLLOWCRV_FIELDS)
#ifndef __cplusplus
#define GOALFOLLOWCRV_C GOAL_FIELDS GOALFOLLOWCRV_FIELDS
#endif

/* 0xA7 (167) GoalFollowCrvAnim, 0xF0 bytes: a GoalFollowCrv that plays an animation goal while it walks (GoalFollowCrvAnim_SetState,
   slot 15). GoalFollowRoute_SetState starts it. */
#define GOALFOLLOWCRVANIM_FIELDS \
    /* 0xC0 */ s32 kind;            /* GoalFollowCrvAnim_SetState: the sgs of the idle animation goal; 8 means "look at ptarget" */ \
    /* 0xC4 */ f32 field_0xC4;     /* GoalFollowCrvAnim_Init sets 1.0 (a method of the class) */ \
    /* 0xC8 */ struct LO *ptarget;  /* GoalFollowCrvAnim_SetState */ \
    u8 unknown_0xCC[0x4]; \
    /* 0xD0 */ QW posLast;          /* GoalFollowCrvAnim_SetState */ \
    /* 0xE0 */ f32 tStuck;          /* GoalFollowCrvAnim_SetState */ \
    u8 unknown_0xE4[0xC];
GOAL_CLASS(GOALFOLLOWCRVANIM, GOALFOLLOWCRV, GOALFOLLOWCRVANIM_FIELDS)

/* 0xA8 (168) GoalFollowCrvVjoy, 0xE0 bytes: a GoalFollowCrv run by a player (a JT: GOAL_JT), which steers the player's virtual joystick
   (JT::PvVjoy()) along the curve. Init func_00144B28, Activate GoalFollowCrvVjoy_Activate, Update GoalFollowCrvVjoy_Update, FillVjoy
   GoalFollowCrvVjoy_FillVjoy. GoalPartnerFollow_SetState (state 0) gets it by class id and sets the three fields below. */
#define GOALFOLLOWCRVVJOY_FIELDS \
    /* 0xC0 */ struct JOY *pjoy;    /* the leader's controller: GoalPartnerFollow_SetState */ \
    /* 0xC4 */ s32 kind;            /* GoalPartnerFollow_SetState sets 8 */ \
    /* 0xC8 */ f32 tDelay;          /* GoalPartnerFollow_SetState: a random 0.1 to 0.3 */ \
    u8 unknown_0xCC[0x4]; \
    /* 0xD0 */ f32 field_0xD0;      /* GoalFollowCrvVjoy_Init (func_00144B28, a method of the class) sets 1.0 */ \
    u8 unknown_0xD4[0xC];
GOAL_CLASS(GOALFOLLOWCRVVJOY, GOALFOLLOWCRV, GOALFOLLOWCRVVJOY_FIELDS)

/* 0xAA (170) GoalIdle, 0x50 bytes: GoalIdle_Init, _Activate, _Deactivate, _Update, _SetState (all four agree on every field) */
#define GOALIDLE_FIELDS \
    /* 0x30 */ f32 tScriptLimit;    /* when state 0 (the guard script) gives way to waiting: set on entering states 1 and 2, read by Update */ \
    /* 0x34 */ f32 tWaitLimit;      /* set on entering state 0, read by Update in state 1 */ \
    /* 0x38 */ s32 state;           /* GoalIdle_Init writes -1 */ \
    /* 0x3C */ f32 tState;          /* GoalIdle_SetState: the time of the last state change */ \
    /* 0x40 */ void *pscript;       /* GoalIdle_SetState passes it to SetGuardScript; GoalIdle_Update clears it when the script is done */ \
    u8 unknown_0x44[0xC];
GOAL_CLASS(GOALIDLE, GOAL, GOALIDLE_FIELDS)

/* 0xAB (171) GoalSearch, 0xE0 bytes: Init func_00171F58, Activate func_00171FA0, Deactivate func_00171FD0, Update func_00172018,
   SetSearchState, SetSearchGoal, func_00172550 (done), func_00172560 */
#define GOALSEARCH_FIELDS \
    /* 0x30 */ s32 state;           /* SetSearchState; func_00172550 tests -1 */ \
    /* 0x34 */ f32 tState;          /* SetSearchState */ \
    /* 0x38 */ f32 field_0x38;      /* func_00171F58, func_00172560, SetSearchState */ \
    /* 0x3C */ f32 field_0x3C;      /* func_00172560 */ \
    /* 0x40 */ f32 field_0x40;      /* func_00171F58 */ \
    /* 0x44 */ struct GOAL *pgoalSearch; /* SetSearchGoal */ \
    /* 0x48 */ s32 fChanged;        /* SetSearchGoal, SetSearchState */
GOAL_CLASS(GOALSEARCH, GOAL, GOALSEARCH_FIELDS)

#ifdef __cplusplus
#define GOALJUMP_PIPE union { struct PIPE *ppipe; s32 fFacing; };
#else
#define GOALJUMP_PIPE s32 fFacing;
#endif
/* 0xAC (172) GoalJump, 0xA0 bytes: Init func_00179F70, GoalJump_Activate, Deactivate func_0017A3D0, Update func_0017A400 (GoalAnim's
   slots 11 to 13). func_0017E9B0 starts it with a point. */
#define GOALJUMP_FIELDS \
    /* 0x50 */ QW posTarget;        /* GoalJump_Activate; func_0017E9B0 sets it */ \
    /* 0x60 */ struct LO *ploTarget; /* GoalJump_Activate */ \
    /* 0x64 */ GOALJUMP_PIPE        /* GoalJump_Activate: the pipe of a JT target, else a facing flag (copied to the jumper) */ \
    /* 0x68 */ s32 fTrackTarget;    /* GoalJump_Activate copies it to the jumper; func_0017E9B0 sets 1 */ \
    /* 0x6C */ s32 fMatrix;         /* GoalJump_Activate sets it with mat; func_0017A400 tests it */ \
    /* 0x70 */ struct MATRIX3Q mat; /* GoalJump_Activate; func_0017A400 hands it to func_00209840 */
GOAL_CLASS(GOALJUMP, GOALANIM, GOALJUMP_FIELDS)

/* 0xAD (173) GoalStand, 0x40 bytes: Init func_0017B590, Activate func_0017B5C0, Deactivate func_0017B5F0, Update func_0017B620,
   FHandleMessage func_0017B690, SetState func_0017B750, done func_0017B7F8. State 0 stands in an animation goal (0x9D). */
#define GOALSTAND_FIELDS \
    /* 0x30 */ s32 state;           /* func_0017B590 writes -1; func_0017B750, func_0017B620, func_0017B7F8 */ \
    /* 0x34 */ f32 tState;          /* func_0017B750 stores the clock on every state change */ \
    /* 0x38 */ struct LO *ptarget;  /* func_0017B750 hands it to the animation goal's ptarget */ \
    u8 unknown_0x3C[0x4];
GOAL_CLASS(GOALSTAND, GOAL, GOALSTAND_FIELDS)

/* 0xAF (175) GoalFlinch, 0x60 bytes: Init func_0017A4B0, Activate func_0017A4E8, Deactivate func_0017A558, Update func_0017A670,
   GoalFlinch_SetState (GoalAnim's slots 11 to 13) */
#define GOALFLINCH_FIELDS \
    /* 0x50 */ s32 stateFlinch;     /* func_0017A4B0 writes -1; GoalFlinch_SetState */ \
    u8 unknown_0x54[0xC];
GOAL_CLASS(GOALFLINCH, GOALANIM, GOALFLINCH_FIELDS)

/* 0xB0 (176), 0x40 bytes, no recovered name: Init func_0017A6F8, Activate func_0017A730, Deactivate func_0017A7B8, Update func_0017A7F8,
   SetState func_0017A8C8, done func_0017A9C0. The brain's command 6 starts it with its object. */
#define GOALB0_FIELDS \
    /* 0x30 */ s32 state;           /* func_0017A6F8 writes -1; func_0017A8C8, func_0017A9C0 */ \
    /* 0x34 */ f32 tState;          /* func_0017A8C8 */ \
    u8 unknown_0x38[0x4]; \
    /* 0x3C */ void *phitter;       /* func_0017A730 hands it to func_00154038; GoalBrain_SetCommand (command 6) sets it */
GOAL_CLASS(GOALB0, GOAL, GOALB0_FIELDS)

/* 0xB1 (177) GoalGrab, 0x70 bytes: GoalGrab_Init, GoalGrab_Activate, GoalAnimLeap_Deactivate, Update func_0017AC90, slot 12
   func_0017B578, GoalAnimLeap_FHandleMessage, GoalAnimLeap_SetState: the guard holds on to its target (sgs 0x17) */
#define GOALGRAB_FIELDS \
    /* 0x50 */ s32 phase;           /* GoalGrab_Init writes -1, GoalAnimLeap_SetState; func_0017B578, GoalAnimLeap_FHandleMessage, func_00206380,
                                       GoalBrain_Update read it */ \
    u8 unknown_0x54[0x4]; \
    /* 0x58 */ s32 chit;            /* GoalAnimLeap_FHandleMessage counts the hits; CHitClingingGuard returns it */ \
    /* 0x5C */ struct SO *psoHeld;  /* GoalBrain_SetCommand (command 7) sets it; func_00206380 compares its poxa; func_00208E70;
                                       GoalGrab_Activate hands it to func_00154038 */ \
    /* 0x60 */ s32 field_0x60;      /* func_001431D0 clears it (a function that gets the goal by class id) */ \
    u8 unknown_0x64[0xC];
GOAL_CLASS(GOALGRAB, GOALANIM, GOALGRAB_FIELDS)

/* 0xB2 (178), 0x50 bytes, no recovered name: Init func_0017B808, Activate func_0017B840, Deactivate func_0017B870, Update
   func_0017BD78, SetState func_0017B8B0. State 0 watches (0x9E), 1 turns to the picker (GoalNotice), 2 watches with sgs 1. */
#define GOALB2_FIELDS \
    /* 0x30 */ s32 state;           /* func_0017B808 writes -1; func_0017B8B0 */ \
    /* 0x34 */ f32 tState;          /* func_0017B8B0 */ \
    u8 unknown_0x38[0x8]; \
    /* 0x40 */ struct LO *ppick;    /* func_0017B8B0 hands it to GoalNotice's ptarget */ \
    u8 unknown_0x44[0xC];
GOAL_CLASS(GOALB2, GOAL, GOALB2_FIELDS)

/* 0xB3 (179), 0x40 bytes, no recovered name: Init func_0017BED0, Activate func_0017BF08, Deactivate func_0017BFB8, Update
   func_0017C3E8, SetState func_0017C550 */
#define GOALB3_FIELDS \
    /* 0x30 */ s32 state;           /* func_0017BED0 writes -1; func_0017C550 */ \
    u8 unknown_0x34[0xC];
GOAL_CLASS(GOALB3, GOAL, GOALB3_FIELDS)

/* 0xB7 (183) GoalGotoTarget, 0x70 bytes: Init func_0017C638, Activate func_0017C6A0, Deactivate func_0017C670, Update func_0017C6D0,
   SetState func_0017C928: goes to an object (state 0), or to a point relative to it (1), or alerts at it (2). The brain's command
   16 starts it with the guard's goto target (SetGuardGotoTarget updates the running one). */
#define GOALGOTOTARGET_FIELDS \
    /* 0x30 */ struct LO *ptarget;  /* func_0017C928: PosLoWorld and ConvertAloPos take it; SetGuardGotoTarget, GoalBrain_SetCommand set it */ \
    u8 unknown_0x34[0xC]; \
    /* 0x40 */ QW offset;           /* func_0017C928 converts it with ConvertAloPos; SetGuardGotoTarget, GoalBrain_SetCommand set it */ \
    /* 0x50 */ s32 state;           /* func_0017C638 writes -1; func_0017C928 */ \
    /* 0x54 */ f32 tState;          /* func_0017C928 */ \
    u8 unknown_0x58[0x8]; \
    /* 0x60 */ QW pos;              /* func_0017C928 */
GOAL_CLASS(GOALGOTOTARGET, GOAL, GOALGOTOTARGET_FIELDS)

/* 0xB8 (184), 0x40 bytes, no recovered name: Init func_0017CAC8, Activate func_0017CB10, Deactivate func_0017CB40, SetState
   func_0017CD00 */
#define GOALB8_FIELDS \
    /* 0x30 */ s32 state;           /* func_0017CAC8 writes -1; func_0017CD00 */ \
    /* 0x34 */ f32 tState;          /* func_0017CD00 */ \
    /* 0x38 */ f32 field_0x38;      /* func_0017CAC8 writes 1.0 */ \
    /* 0x3C */ s32 field_0x3C;      /* func_0017CD00 */
GOAL_CLASS(GOALB8, GOAL, GOALB8_FIELDS)

/* 0xBA (186) GoalGoto, 0xD0 bytes: Init func_0017D360, Activate func_0017D3B0, Deactivate func_0017D408, Update func_0017D6C8,
   GoalGoto_SetState, func_0017D8A8 (finds the path), GoalGoto_FArrived */
#define GOALGOTO_FIELDS \
    /* 0x30 */ s32 state;           /* GoalGoto_Init writes -1; GoalGoto_SetState, GoalGoto_FArrived, GoalGoto_FBlocked (states 1 and 2 follow the curve) */ \
    /* 0x34 */ f32 tState;          /* GoalGoto_SetState: the clock at the last state change */ \
    /* 0x38 */ s32 field_0x38;      /* GoalGoto_Activate adds it to the guard's sgs unless -1, GoalGoto_Deactivate removes it; GoalGoto_Init writes -1; func_0017E278, func_0017C928 set 0x1C */ \
    u8 unknown_0x3C[0x4]; \
    /* 0x40 */ struct GOALTARGET target;   /* SetGoalTarget; func_0017D8A8 resolves it */ \
    /* 0x60 */ struct GOALTARGET targetResolved; /* func_0017D8A8: target, or the near end of the path */ \
    /* 0x80 */ struct GOALTARGET targetSnap; /* GoalGoto_SetState (state 5) copies it to the snap goal's target */ \
    /* 0xA0 */ f32 field_0xA0;      /* GoalGoto_Init writes the smallest float */ \
    /* 0xA4 */ s32 field_0xA4;      /* GoalGoto_Init copies it from the world's word at 0x28 (B_003E1A5C) */ \
    /* 0xA8 */ struct LO *ptarget;  /* func_0017C928; GoalGoto_SetState hands it to the animation and follow goals */ \
    /* 0xAC */ s32 field_0xAC;      /* func_0017C928 sets 1; GoalGoto_SetState tests it */ \
    u8 unknown_0xB0[0x4]; \
    /* 0xB4 */ s32 cpzlink;         /* func_0017D8A8: the path's links */ \
    /* 0xB8 */ struct PZLINK *apzlink[1]; /* func_0017D8A8; GoalGoto_SetState hands the first word to the route goal */ \
    /* 0xBC */ s32 fStraight;       /* func_0017D8A8: no path search; GoalGoto_SetState copies it to the follow goal */ \
    /* 0xC0 */ s32 fLink;           /* func_0017D8A8: a partial path is fine; SetSearchState, func_0017C928, func_0017E278 set 1 */ \
    u8 unknown_0xC4[0xC];
GOAL_CLASS(GOALGOTO, GOAL, GOALGOTO_FIELDS)

/* 0xBD (189) GoalFlee, 0x50 bytes: Init func_0017DD70, Activate func_0017DDA8, Deactivate func_0017DDE8, Update func_0017DE50,
   SetState func_0017E278, done func_0017DE40. The brain's command 18 starts it. */
#define GOALFLEE_FIELDS \
    /* 0x30 */ s32 state;           /* -1 before Activate, 0 idle, 1 run, 2 alert (SetState); func_0017DE40 tests -1 */ \
    /* 0x34 */ f32 tState;          /* the clock at the last state change (SetState) */ \
    /* 0x38 */ struct LO *ptarget;  /* func_0017DDA8 hands it to func_00208540 (the guard's alert object); SetState gives it to the
                                       idle goal; GoalBrain_SetCommand (command 18) sets it */ \
    u8 unknown_0x3C[0x4]; \
    /* 0x40 */ f32 field_0x40;      /* GoalBrain_SetCommand (command 18): the command's float */ \
    u8 unknown_0x44[0xC];
GOAL_CLASS(GOALFLEE, GOAL, GOALFLEE_FIELDS)

/* 0xBE (190) GoalFollowRoute, 0x50 bytes: Init func_0017E3A0, Activate func_0017E3D8, Deactivate func_0017E410, Update func_0017E458,
   done func_0017E570, NextWaypoint func_0017E580, SetState func_0017E6B0 */
#define GOALFOLLOWROUTE_FIELDS \
    /* 0x30 */ struct ROUTE *proute; /* NextWaypoint, SetState */ \
    /* 0x34 */ s32 index;           /* the waypoint being walked to (NextWaypoint increments it) */ \
    /* 0x38 */ s32 state;           /* -1 before Activate (Init sets it, done tests it), 0 walking, 1 acting at the waypoint */ \
    /* 0x3C */ f32 tState;          /* the clock at the last state change */ \
    /* 0x40 */ f32 tEnd;            /* SetState state 0: the clock when the walk should be over */ \
    u8 unknown_0x44[0xC];
GOAL_CLASS(GOALFOLLOWROUTE, GOAL, GOALFOLLOWROUTE_FIELDS)

/* 0xBF (191) GoalSnapToPoint, 0x50 bytes: Init func_0017E888, Activate func_0017E8B8, Deactivate func_0017E8E8, Update func_0017E918,
   Snap func_0017E9B0. GoalFollowRoute_SetState and the brain's command 19 start it with a point. */
#define GOALSNAPTOPOINT_FIELDS \
    /* 0x30 */ struct GOALTARGET target; /* func_0017E9B0 resolves it (func_001C1EC0) and snaps the guard to the surface below */
GOAL_CLASS(GOALSNAPTOPOINT, GOAL, GOALSNAPTOPOINT_FIELDS)

/* 0xC0 (192) GoalFollowCurve, 0x60 bytes: Init func_0017EB48, Activate func_0017EB88, Deactivate func_0017EC80, Update func_0017ECB0,
   Advance func_0017ECF0 */
#define GOALFOLLOWCURVE_FIELDS \
    u8 unknown_0x30[0x8]; \
    /* 0x38 */ f32 s;               /* the curve parameter, -1.0 before Activate (Init) */ \
    u8 unknown_0x3C[0x24];
GOAL_CLASS(GOALFOLLOWCURVE, GOAL, GOALFOLLOWCURVE_FIELDS)

/* 0xC2 (194) GoalPartnerFollow, 0xA0 bytes: a partner (a JT: GOAL_JT) follows the leader. Init GoalPartnerFollow_Init, Activate
   func_00145080, Deactivate func_001450B0, Update GoalPartnerFollow_Update; GoalPartnerFollow_SetState (func_00145B18) */
#define GOALPARTNERFOLLOW_FIELDS \
    /* 0x30 */ struct LO *ploLeader; /* the leader it follows: GoalPartnerFollow_PpathzoneTarget, GoalPartnerFollow_SetState */ \
    u8 unknown_0x34[0x2C]; \
    /* 0x60 */ s32 state;           /* GoalPartnerFollow_SetState; Activate sets 0, Deactivate -1 through it */ \
    /* 0x64 */ f32 tState;          /* GoalPartnerFollow_SetState: the time of the change */ \
    u8 unknown_0x68[0x18]; \
    /* 0x80 */ QW posWarp;          /* GoalPartnerFollow_SetState (state 1) passes it to WarpJtToPoint */ \
    /* 0x90 */ struct LO *ploTarget; /* GoalPartnerFollow_SetState (state 2) hands it to the attack goal it starts */ \
    u8 unknown_0x94[0xC];
GOAL_CLASS(GOALPARTNERFOLLOW, GOAL, GOALPARTNERFOLLOW_FIELDS)

/* 0xC3 (195) GoalPartnerAttackMurray, 0xC4 (196) GoalPartnerAttackBentley, 0xC5 (197) GoalPartnerAttackSly: three classes of 0x40 bytes
   with the same layout and the same shape of methods (Init, Activate, Deactivate func_00145D68/func_00146260/func_00146758, Update,
   FillVjoy, SetState func_00146158/func_00146650, FIdle). GoalPartnerFollow_SetState starts the one of the partner's class. */
#define GOALPARTNERATTACK_FIELDS \
    /* 0x30 */ s32 state;           /* the SetState methods; the FIdle methods test -1 */ \
    /* 0x34 */ f32 tState;          /* the SetState methods */ \
    /* 0x38 */ struct LO *ploTarget; /* GoalPartnerFollow_SetState sets it before Activate */ \
    u8 unknown_0x3C[0x4];
GOAL_CLASS(GOALPARTNERATTACK, GOAL, GOALPARTNERATTACK_FIELDS)

#ifdef __cplusplus
#if defined(__mips__)
SLY2_SIZE_CHECK(GOALBRAIN, 0xB0);
SLY2_SIZE_CHECK(GOALANIM, 0x50);
SLY2_SIZE_CHECK(GOALTRACK, 0x60);
SLY2_SIZE_CHECK(GOALHIT, 0xC0);
SLY2_SIZE_CHECK(GOALREACT, 0x50);
SLY2_SIZE_CHECK(GOALNOTICE, 0x60);
SLY2_SIZE_CHECK(GOALFOLLOWCRV, 0xC0);
SLY2_SIZE_CHECK(GOALFOLLOWCRVANIM, 0xF0);
SLY2_SIZE_CHECK(GOALIDLE, 0x50);
SLY2_SIZE_CHECK(GOALJUMP, 0xA0);
SLY2_SIZE_CHECK(GOALSTAND, 0x40);
SLY2_SIZE_CHECK(GOALFLINCH, 0x60);
SLY2_SIZE_CHECK(GOALB0, 0x40);
SLY2_SIZE_CHECK(GOALGRAB, 0x70);
SLY2_SIZE_CHECK(GOALB2, 0x50);
SLY2_SIZE_CHECK(GOALB3, 0x40);
SLY2_SIZE_CHECK(GOALGOTOTARGET, 0x70);
SLY2_SIZE_CHECK(GOALB8, 0x40);
SLY2_SIZE_CHECK(GOALGOTO, 0xD0);
SLY2_SIZE_CHECK(GOALFLEE, 0x50);
SLY2_SIZE_CHECK(GOALFOLLOWROUTE, 0x50);
SLY2_SIZE_CHECK(GOALSNAPTOPOINT, 0x50);
SLY2_SIZE_CHECK(GOALFOLLOWCURVE, 0x60);
SLY2_SIZE_CHECK(GOALFOLLOWCRVVJOY, 0xE0);
SLY2_SIZE_CHECK(GOALPARTNERFOLLOW, 0xA0);
SLY2_SIZE_CHECK(GOALPARTNERATTACK, 0x40);
SLY2_OFFSET_CHECK(GOALFOLLOWCRV, posGoal, 0x80);
SLY2_OFFSET_CHECK(GOALFOLLOWCRVVJOY, pjoy, 0xC0);
SLY2_OFFSET_CHECK(GOALPARTNERFOLLOW, posWarp, 0x80);
SLY2_OFFSET_CHECK(GOALPARTNERATTACK, ploTarget, 0x38);
SLY2_OFFSET_CHECK(GOALHIT, args, 0x50);
SLY2_OFFSET_CHECK(GOALHIT, tJolt, 0xB0);
SLY2_OFFSET_CHECK(GOALGRAB, psoHeld, 0x5C);
SLY2_OFFSET_CHECK(GOALJUMP, mat, 0x70);
SLY2_OFFSET_CHECK(GOALGOTO, fLink, 0xC0);
SLY2_OFFSET_CHECK(GOALFOLLOWCRVANIM, tStuck, 0xE0);
SLY2_OFFSET_CHECK(GOALGOTOTARGET, pos, 0x60);
SLY2_OFFSET_CHECK(GOALBRAIN, tRetry, 0xA4);
#endif
#endif
#endif
