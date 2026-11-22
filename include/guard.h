/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The objects a guard (STEPGUARD, stepguard.h) holds or points at, for C and C++: its animation references (ANIMREF, the table
   entries GUARDANIM, the jump block JUMPANIM and the JUMPER a jump animation drives), its heading controller GUARDHEADING, its
   home, damage and aim records, its SENSOR and the ALERT it shares with the guards that watch the same object.
   A field is listed with its readers (the field rule of lo.h); a C source gets the same layout as plain structs (SENSOR is a LO
   in C++, so in C its first 0x50 bytes are unknown). */
#ifndef SLY2_GUARD_H
#define SLY2_GUARD_H
#include "types.h"
#ifdef __cplusplus
#include "lo.h"
#endif

struct STEP;
struct STEPGUARD;
struct OXA;
struct LO;

/* An animation reference, 0x10 bytes: `kind` says what `pdata` points at (BindAnimref sets it: 0 a plain object, 1 an object kept
   as is, 2 a JUMPANIM block of 0x40 bytes from the slot heap, 3 a direction-animation set of 0xD0 bytes, -1 none); ResetAnimref
   frees the block of kinds 2 and 3. StartAnimref takes the same four words (kind, pv, pinst, n). */
struct ANIMREF {
    /* 0x0 */ s32 kind;    /* BindAnimref, ResetAnimref, CloneAnimref; func_00174EA0, func_001751F0, GoalHit_Activate test 2 */
    /* 0x4 */ void *pdata; /* ResetAnimref, UseGuardAnimation, func_00207D98; GoalAnimLeap_FHandleMessage passes it to PeaFindAsegLabel */
    /* 0x8 */ void *pinst; /* the playing instance: GoalAnimLeap_FHandleMessage seeks it (SeekAsega); for kind 2 the JUMPER
                              (GoalHit_Activate, func_00175258 and func_001751F0 steer it) */
    /* 0xC */ u32 grf;     /* UseGuardAnimation stores its fourth argument, func_00207D98 clears it; GoalAnimLeap_FHandleMessage
                              starts the animation again with grf | 1 (StartAnimref's flags) */
};

/* the 0x40-byte block of a kind-2 ANIMREF (from the slot heap) */
struct JUMPANIM {
    /* 0x0 */ s32 field_0x0;  /* func_0020BD78 sets -1, func_00207D98 then stores its id */
    /* 0x4 */ void *pobject;  /* BindAnimref */
    u8 unknown_0x8[0x14];
    /* 0x1C */ f32 distance;  /* GoalHit_Activate: the length of the jump it aims (only for kind 2, so the block is certain) */
    u8 unknown_0x20[0x20];
};

/* a jump in progress, the instance of a kind-2 ANIMREF. Its methods: UpdateJumper (func_0020C0E8), SetJumperTarget, SetJumperState */
struct JUMPER {
    u8 unknown_0x0[0x10];
    /* 0x10 */ s32 state;           /* UpdateJumper switches on it; SetJumperTarget; func_00174EA0 */
    /* 0x14 */ f32 tState;          /* UpdateJumper */
    u8 unknown_0x18[0x1C];
    /* 0x34 */ struct STEP *pso;    /* UpdateJumper: the jumping actor */
    /* 0x38 */ void *pasega;        /* UpdateJumper */
    u8 unknown_0x3C[0x14];
    /* 0x50 */ f32 tLand;           /* UpdateJumper */
    /* 0x54 */ f32 tLandStart;      /* UpdateJumper */
    /* 0x58 */ struct LO *ploTarget; /* GoalJump_Activate copies its goal's target */
    /* 0x5C */ s32 fFacing;         /* GoalJump_Activate copies its goal's fFacing */
    /* 0x60 */ s32 fTrackTarget;    /* SetJumperTarget follows the target in flight while it is set, UpdateJumper tests it, func_001751F0 sets it */
    /* 0x64 */ s32 field_0x64;      /* func_001751F0 sets it */
};

/* one entry of a guard's animation table (0x20 bytes): an ANIMREF and the sgs group it plays for */
struct GUARDANIM {
    /* 0x0 */ struct ANIMREF ref;
    /* 0x10 */ u64 grf; /* PguardanimEnsure (its key), PguardanimBestMatch */
    u8 unknown_0x18[0x8];
};

/* a rotation matrix held as three quadword rows (copied with lq/sq): func_00209840 copies one into the actor's heading,
   GoalJump_Activate builds one in its goal */
struct MATRIX3Q {
    QW row[3];
};

/* a guard's heading controller, 0x10 bytes embedded at STEPGUARD 0xFD0. While fHold is 0 it applies the guard's heading to its
   STEP (func_00209818 sets the target radian, func_00209840 copies a rotation matrix in) */
struct GUARDHEADING {
    /* 0x0 */ void *field_0x0;    /* GrfGuardCustomXps (85) reads it */
    /* 0x4 */ s32 fHold;          /* func_002097C8 sets 1, func_002097D8 clears it; func_00209818 and func_00209840 act only at 0 */
    u8 unknown_0x8[0x4];
    /* 0xC */ struct STEP *pstep; /* func_00209768 and func_00209770 set it (CloneGuard passes the guard); func_00209818, func_00209840 */
};

/* a guard's home record (OnGuardAdd fills it from the guard's start position and heading) */
struct HOME {
    u8 unknown_0x0[0x8];
    /* 0x8 */ void *pposHome; /* OnGuardAdd */
    /* 0xC */ f32 yaw;        /* OnGuardAdd */
};

struct FALLCHECK;

/* a guard's aim state: UpdateGuard waits for its animation reference to finish */
struct AIMSTATE {
    u8 unknown_0x0[0xC0];
    /* 0xC0 */ struct ANIMREF *panimref; /* UpdateGuard */
};

/* a guard's damage record: SetGuardDamageSource (0x20D460) stores the source of the last hit at 0xC */
struct GUARDDAMAGE {
    u8 unknown_0x0[0xC];
    /* 0xC */ void *psource; /* HandleStepguardMessage */
};

/* SENSOR, the sensor object a guard owns (STEPGUARD::psensor): a LO subclass (its vtable is at 0xC and CloneGuard calls its slot
   41), size not known. OnGuardAdd (26) sets powner and poxa, ClearGuardSensing clears 0xFC; func_00259D38/48/70 are its setters and
   getter of 0xE8 and 0xEC; func_00208BE0 (89) reads the volume at 0xE8. */
#ifdef __cplusplus
struct SENSOR : LO {
    u8 unknown_0x50[0x90];
#else
struct SENSOR {
    u8 unknown_0x0[0xE0];
#endif
    /* 0xE0 */ void *powner;     /* OnGuardAdd (26): the guard */
    /* 0xE4 */ struct OXA *poxa; /* OnGuardAdd (26): the guard's poxa */
    /* 0xE8 */ void *pvolume;    /* func_00259D38 sets it; func_00208BE0 tests its grfo bit 60 and hands it to func_00227C90 */
    /* 0xEC */ s32 field_0xEC;   /* func_00259D48 sets it, func_00259D70 returns it */
    u8 unknown_0xF0[0xC];
    /* 0xFC */ s32 field_0xFC;   /* ClearGuardSensing clears it */
};

/* ALERT, the shared alarm of the guards that watch one object: 0xAC bytes (PalertEnsure allocates it), kept in the list at
   B_003E145C by InitAlert. AddAlertGuard stores a guard in apguard[] and counts it, RemoveAlertGuard takes it out. */
struct ALERT {
    /* 0x0 */ f32 tStart;       /* AddAlertGuard stores the game time when the first guard joins */
    u8 unknown_0x4[0x4];
    /* 0x8 */ s32 field_0x8;    /* InitAlert: -1 */
    /* 0xC */ struct LO *palo;  /* InitAlert: its second argument, the object PalertFind searches for; func_0017C3E8 and func_0017C550 read it */
    /* 0x10 */ s32 field_0x10;  /* InitAlert: -1 */
    /* 0x14 */ f32 field_0x14;  /* InitAlert: 1.0 */
    /* 0x18 */ f32 radCone;     /* InitAlert: 2.0; func_0017C3E8 compares an angle with it */
    u8 unknown_0x1C[0xC];
    /* 0x28 */ s32 cguard;      /* AddAlertGuard, RemoveAlertGuard */
    /* 0x2C */ struct STEPGUARD *apguard[8]; /* AddAlertGuard, RemoveAlertGuard */
    u8 unknown_0x4C[0x60];
};
#endif
