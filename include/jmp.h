/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JMP, the player's jump part (InitJt starts it in place at JT + 0x2C0: JT::PvJmp). One header for InitJmp (0x195950) and the
   source file of 0x195FB8-0x199400, which hold its functions. The fields are those these functions read or set; InitJmp is the
   part's own constructor, so the fields it sets are certain. C++ only. */
#ifndef SLY2_JMP_H
#define SLY2_JMP_H
#include "sly2.h"
#include "jt.h"
#include "act.h"

/* what JMP::pasega points at, as the jump code reads it: an LO (grfo at 0x28) with words at 0x10C and 0x124 and a kind at 0x17C
   (SetJmpBodyState takes it; retail also stores it in JT words other code reads as an ASEGA *). Its class is not settled. */
struct JMPASEGA { u8 unknown_0x0[0x28]; u64 grfo; u8 unknown_0x30[0x10C - 0x30]; s32 field_0x10C; u8 unknown_0x110[0x124 - 0x110]; s32 field_0x124; u8 unknown_0x128[0x17C - 0x128]; s32 kind; };

struct EDGEHOST { u8 unknown_0x0[0xEC]; void *poxa; };

struct EDGESO { void *pxf; EDGEHOST *phost; };

struct EDGEEND { EDGESO *pso; u8 unknown_0x4[0xC]; QW pos; u8 unknown_0x20[0x20]; };

struct EDGE { EDGEEND aend[2]; u8 unknown_0x80[0x9C - 0x80]; s32 field_0x9C; s32 field_0xA0; s32 field_0xA4; };


struct LANDING { LO *plo; s32 field_0x4; s32 field_0x8; };

struct SURFACEACT { u8 unknown_0x0[0x148]; unsigned long flags; };

/* what JT::psoSurface points at, as func_001942F0 and UpdateJmpBodyState read it */
struct SURFACE { u8 unknown_0x0[0x40]; int unk40; u8 unknown_0x44[8]; SURFACEACT *act; u8 unknown_0x50[0x10]; QW pos; u8 unknown_0x70[0x18]; float unk88; };

struct JMP {
    /* 0x00 */ JT *pjt;       /* InitJmp (its argument) */
    /* 0x04 */ s32 kind;      /* InitJmp sets -1 */
    /* 0x08 */ s32 field_0x8;
    /* 0x0C */ JMPASEGA *pasega;
    u8 unknown_0x10[4];
    /* 0x14 */ f32 field_0x14;
    u8 unknown_0x18[4];
    /* 0x1C */ s32 state;     /* InitJmp sets -1 */
    /* 0x20 */ float tState;
    /* 0x24 */ s32 field_0x24;
    /* 0x28 */ s32 field_0x28;
    /* 0x2C */ s32 pending;
    /* 0x30 */ s32 fStarted;
    u8 unknown_0x34[0xC];
    /* 0x40 */ s32 field_0x40;
    u8 unknown_0x44[0xC8 - 0x44];
    /* 0xC8 */ EDGESO *psoEdge;
    u8 unknown_0xCC[4];
    /* 0xD0 */ QW posEdge;
    /* 0xE0 */ QW dirEdge;
    /* 0xF0 */ QW vecF0;      /* InitJmp copies the constants at 0x2BF740 here */
    /* 0x100 */ s32 field_0x100;
    /* 0x104 */ s32 field_0x104;
    /* 0x108 */ f32 field_0x108; /* InitJmp sets -60.0 */
    /* 0x10C */ f32 field_0x10C; /* -50.0 */
    /* 0x110 */ f32 field_0x110; /* 75.0 */
    /* 0x114 */ f32 field_0x114; /* 50.0 */
    /* 0x118 */ f32 field_0x118; /* -150.0 */
    /* 0x11C */ f32 field_0x11C; /* 75.0 */
    /* 0x120 */ void *apasegA[5]; /* StartJmpDirectionAseg: the direction animations, picked by field_0x8 (state 2 uses apasegB) */
    /* 0x134 */ void *apasegB[5]; /* StartJmpDirectionAseg; UpdateJmpBodyState applies entry 0 on its own */
    u8 unknown_0x148[0x164 - 0x148];
    /* 0x164 */ f32 field_0x164; /* InitJmp sets 1.0 */
    u8 unknown_0x168[0x1D0 - 0x168];
    /* 0x1D0 */ LANDING landing;
    u8 unknown_0x1DC[0x1F0 - 0x1DC];
    /* 0x1F0 */ ACTVAL *pactval;
};
#endif
