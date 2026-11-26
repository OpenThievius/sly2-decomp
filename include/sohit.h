/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SOHIT, a playable object that takes hits (config/recovered/decomp_names.md: SoHit_Init, SoHit_FTakeHit, SoHit_Kill); Mount,
   Chaser, Grab and Swarm derive from it (they share SoHit_ResetState). A subclass of PO (include/po.h): the fields start at 0x180.
   Declared 0x1C0 bytes (vecKnock makes it 16-aligned; the subclasses' own fields start at 0x1C0: Mount_Init, Grab, Chaser, Swarm); only the fields read so far are declared. Local to the sources that use it until a header is agreed. */
#ifndef SLY2_SOHIT_H
#define SLY2_SOHIT_H
#include "po.h"

/* 8 bytes of a type not known: a copy goes by ldl/ldr (alignment 1), as SoHit_Init copies the constants of 0x2BE7E0 */
struct SOHITBYTES8 { u8 bytes[8]; };

struct SOHIT : PO {
    virtual void Slot82(int arg);       /* 82: RefCallSlot290 (the Splice binding of classes 71 to 76) passes one word (Splice type 0x2030) */
    virtual void Slot83();              /* 83: SoHit_PostLoad (func_0017F138) calls it after PostSoLoad, without arguments; so does RefCallSlot298 (Splice) */
    /* 0x180 */ s32 hpMax;      /* SoHit_ResetState (func_0017F6B0) copies it to hp; Chaser_SetState does the same when its state leaves -1 */
    /* 0x184 */ s32 hp;         /* the same two; Chaser_FTakeHit reads it */
    /* 0x188 */ s32 dhp;        /* SoHit_Kill (the damage it deals on contact); Swarm_AdjustNewXp tests it */
    /* 0x18C */ s32 fTouchQueued; /* SoHit_Reset (func_0017F110) clears it, SoHit_QueueTouch (func_0017F5B0) tests and sets it, SoHit_ResetState (func_0017F6B0) tests it: all three SOHIT methods */
    /* 0x190 */ void *pexpl;   /* reader: SoHit_Kill (a method of SOHIT) passes it to ExplodeExpl when set */
    /* 0x194 */ s32 hAsega;     /* SoHit_SetAnimEntry (func_0017F4C0), SoHit_FAnimDone (func_0017F550): the playing animation's handle */
    /* 0x198 */ s32 hSma;       /* the same two: the SM's handle */
    u8 unknown_0x19C[0x4];
    /* 0x1A0 */ QW vecKnock;    /* SoHit_Init (a method) copies the constants at 0x2BE7D0 here: 300.0, 50.0, 0, 0 */
    /* 0x1B0 */ SOHITBYTES8 field_0x1B0; /* SoHit_Init copies the 8 bytes at 0x2BE7E0 here: 0.0, 800.0 as floats */
    u8 unknown_0x1B8[0x8];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(SOHIT, 0x1C0);
SLY2_OFFSET_CHECK(SOHIT, fTouchQueued, 0x18C);
SLY2_OFFSET_CHECK(SOHIT, vecKnock, 0x1A0);
#endif
#endif
