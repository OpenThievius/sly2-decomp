/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LOOKRIG: the look rig InitBentley starts at BENTLEY + 0x1710 (BENTLEY::PvLookRig(): InitLookRig fills it, UpdateLookRig,
   SetLookRigState, HandleLookRigMessage and UpdateBentleyAim read it). Layout from SetLookRigState (the entries) and InitLookRig;
   the six entries are 0x1C bytes each. C++ only. */
#ifndef SLY2_LOOKRIG_H
#define SLY2_LOOKRIG_H
#include "sly2.h"
#include "jt.h"

struct LOOKRIGENTRY {
    /* 0x00 */ f32 wOld;   /* SetLookRigState */
    u8 unknown_0x4[0x8];
    /* 0x0C */ f32 wNew;   /* SetLookRigState */
    u8 unknown_0x10[0x8];
    /* 0x18 */ void *paseg; /* SetLookRigState */
};

struct LOOKRIG {
    /* 0x00 */ JT *pjt;       /* InitLookRig; HandleLookRigMessage reads JT::field_0x10B8 through it */
    /* 0x04 */ s32 state;     /* InitLookRig sets -1; SetLookRigState, UpdateLookRig, UpdateBentleyAim */
    /* 0x08 */ s32 iHigh;     /* SetLookRigState */
    /* 0x0C */ s32 field_0xC; /* HandleLookRigMessage sets it on message 0x242; UpdateLookRig tests it (fCanRestart there) */
    /* 0x10 */ s32 fSnap;     /* HandleLookRigMessage sets it on message 0x16E; SetLookRigState */
    /* 0x14 */ s32 fReleased; /* reader: UpdateLookRig (a LOOKRIG method) sets it when button 0x80 is up */
    /* 0x18 */ f32 tBlend;    /* SetLookRigState */
    /* 0x1C */ f32 gTarget;   /* SetLookRigState */
    /* 0x20 */ QW vecTarget;  /* SetLookRigState */
    /* 0x30 */ f32 rMin;      /* SetLookRigState */
    /* 0x34 */ f32 rMax;      /* SetLookRigState */
    /* 0x38 */ LOOKRIGENTRY aentry[6]; /* InitLookRig: six 0x1C-byte records */
    /* 0xE0 */ void *phandle; /* SetLookRigState; HandleLookRigMessage compares the sender of message 9 with it */
    /* 0xE4 */ void *palo;    /* SetLookRigState */
};
#endif
