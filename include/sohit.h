/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SOHIT, a playable object that takes hits (config/recovered/decomp_names.md: SoHit_Init, SoHit_FTakeHit, SoHit_Kill); Mount,
   Chaser, Grab and Swarm derive from it (they share SoHit_ResetState). A subclass of PO (include/po.h): the fields start at 0x180.
   Its size is not known: only the fields read so far are declared. Local to the sources that use it until a header is agreed. */
#ifndef SLY2_SOHIT_H
#define SLY2_SOHIT_H
#include "po.h"

struct SOHIT : PO {
    u8 unknown_0x180[0x14];
    /* 0x194 */ s32 hAsega;     /* SoHit_SetAnimEntry (func_0017F4C0), SoHit_FAnimDone (func_0017F550): the playing animation's handle */
    /* 0x198 */ s32 hSma;       /* the same two: the SM's handle */
};
#endif
