/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SOHIT, a playable object that takes hits (config/recovered/decomp_names.md: SoHit_Init, SoHit_FTakeHit, SoHit_Kill); Mount,
   Chaser, Grab and Swarm derive from it (they share SoHit_ResetState). A subclass of PO (include/po.h): the fields start at 0x180.
   Its size is not known: only the fields read so far are declared. Local to the sources that use it until a header is agreed. */
#ifndef SLY2_SOHIT_H
#define SLY2_SOHIT_H
#include "po.h"

struct SOHIT : PO {
    /* 0x180 */ s32 hpMax;      /* SoHit_ResetState (func_0017F6B0) copies it to hp; Chaser_SetState does the same when its state leaves -1 */
    /* 0x184 */ s32 hp;         /* the same two; Chaser_FTakeHit reads it */
    /* 0x188 */ s32 dhp;        /* SoHit_Kill (the damage it deals on contact); Swarm_AdjustNewXp tests it */
    u8 unknown_0x18C[0x8];
    /* 0x194 */ s32 hAsega;     /* SoHit_SetAnimEntry (func_0017F4C0), SoHit_FAnimDone (func_0017F550): the playing animation's handle */
    /* 0x198 */ s32 hSma;       /* the same two: the SM's handle */
};
#endif
