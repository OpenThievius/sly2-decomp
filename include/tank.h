/* SPDX-License-Identifier: GPL-3.0-or-later */
/* TANK, the player's tank turret: a PO (include/po.h) of 0x1E0 bytes whose own fields start at 0x180 (retail's class 69, parent PO 50,
   size 0x1E0, config/recovered/class_diff.tsv; the name follows OnTankActive, PostTankLoad, UpdateTank, UpdateTankAim,
   UpdateTankFire: its own functions, so one reader is enough). Slot 3 is called by UpdateTankFire (HandleSpliceEvent), slot 15 by
   PostTankLoad's base, 16 is UpdateTank, 78 OnTankActive. C++ only. */
#ifndef SLY2_TANK_H
#define SLY2_TANK_H
#include "po.h"
#include "clq.h"

struct ACT;
struct LAUNCH;

/* LM (a range; UpdateTankAim limits the pan and tilt with GLimitLm): clq.h */

/* the controller words UpdateTankAim reads from PO::pjoy's block (JOY, include/joy.h, leaves them unknown): a local view,
   read here only */
struct JOYSTICKVIEW {
    u8 unknown_0x0[0x10];
    /* 0x10 */ f32 xLeft;  /* UpdateTankAim: added to xRight for the pan */
    /* 0x14 */ f32 yLeft;  /* UpdateTankAim: the tilt */
    u8 unknown_0x18[0x8];
    /* 0x20 */ f32 xRight;
};

struct TANK : PO {
    /* 0x180 */ struct LO *ploAim;    /* UpdateTankAim: the object the barrel follows while fAim is set */
    /* 0x184 */ s32 fAim;             /* UpdateTankAim */
    u8 unknown_0x188[0x4];
    /* 0x18C */ f32 pan;              /* UpdateTankAim; func_00226370 builds the act's rotation from it */
    /* 0x190 */ f32 tilt;             /* the same */
    /* 0x194 */ f32 panRate;          /* UpdateTankAim */
    /* 0x198 */ f32 tiltRate;         /* UpdateTankAim */
    /* 0x19C */ LM lmTilt;            /* UpdateTankAim limits tilt with it */
    /* 0x1A4 */ LM lmPan;             /* UpdateTankAim limits pan with it */
    u8 unknown_0x1AC[0x10];
    /* 0x1BC */ f32 skill;            /* UpdateTankAim scales the turn speed and its limit by it */
    /* 0x1C0 */ struct LO *ploCloneSrc; /* UpdateTankFire leases a clone of it (PloLeaseCloneObject); FIgnoreTankIntersection compares its scope */
    /* 0x1C4 */ struct LAUNCH *plaunch; /* UpdateTankFire aims the clone with it (LaunchSoAtTarget) */
    /* 0x1C8 */ struct SO *psoClone;  /* UpdateTankFire: the clone it leased */
    /* 0x1CC */ s32 fRotAct;          /* PostTankLoad clears it and restarts the act (func_00226370); UpdateTankAim tests it */
    u8 unknown_0x1D0[0x8];
    /* 0x1D8 */ struct ACT *pact;     /* the rotation act func_00226370 starts and stops; UpdateTankAim updates it */
    u8 unknown_0x1DC[0x4];
    /* PO::pjoy's block as the stick words UpdateTankAim reads (JOY leaves them unknown); an accessor, as STEP::pgoalstack() */
    struct JOYSTICKVIEW *pstick() { return (struct JOYSTICKVIEW *)pjoy; }
};

#if defined(__mips__)
SLY2_SIZE_CHECK(TANK, 0x1E0);
SLY2_OFFSET_CHECK(TANK, ploAim, 0x180);
SLY2_OFFSET_CHECK(TANK, pan, 0x18C);
SLY2_OFFSET_CHECK(TANK, lmTilt, 0x19C);
SLY2_OFFSET_CHECK(TANK, lmPan, 0x1A4);
SLY2_OFFSET_CHECK(TANK, skill, 0x1BC);
SLY2_OFFSET_CHECK(TANK, ploCloneSrc, 0x1C0);
SLY2_OFFSET_CHECK(TANK, fRotAct, 0x1CC);
SLY2_OFFSET_CHECK(TANK, pact, 0x1D8);
#endif
#endif
