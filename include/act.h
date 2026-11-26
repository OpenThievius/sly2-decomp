/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ACT, an actuator of an XF: a pooled object (PactNew 0x12E238 allocates it from the act slot heap, PactNewForXf 0x12DB50 fills the
   header, InsertXfAct links it) with its vtable pointer at 0x18. The header (0x00 to 0x1B) is common to every kind; a kind's own fields
   start at 0x1C: ACTASEG (kind 0, 0x2C bytes: ApplyAseg's, which an ASEGA lists; SeekAsega, SnapAsega walk the list), ACT1 (kind 1:
   PactNew sets 0x1C to 2), ACT2 (kind 2, 0x80 bytes: two quadratics and two ranges, read by LoadAloFromBrx), ACT4 (kind 4: two
   floats), ACT9 (kind 9: a vector), ACTVAL (kind 8: SetActvalGoal copies its goals to the transform's posGoal and velGoal).
   palo, pxf, priority and xfk are written by PactNewForXf from its arguments: the roles of palo and priority come from the argument
   order of the Create* callers (uncertain); pxf is certain (GetActvalPositionGoal, func_0012DEF0 read it as the XF); ApplyAseg sets
   xfk to 5 or 7, PactNew kind 9 to 0x14. C and C++. */
#ifndef SLY2_ACT_H
#define SLY2_ACT_H
#include "xf.h"
#include "clq.h"

struct ALO;
struct ASEGA;
struct ASEGANIM;

struct ACT {
    /* 0x00 */ s32 kind;      /* PactNew */
    /* 0x04 */ struct ALO *palo; /* PactNewForXf */
    /* 0x08 */ struct XF *pxf; /* PactNewForXf */
    /* 0x0C */ s32 priority;  /* PactNewForXf; ApplyAseg copies ASEG::priorityAct */
    /* 0x10 */ struct ACT *pactNext; /* the next act on the transform (XF::pactFirst): func_00131B10 walks it; ACTADJ keeps its pactNext in the same word */
    /* 0x14 */ s32 xfk;       /* PactNewForXf; ApplyAseg (5 or 7), PactNew kind 9 (0x14) */
    /* 0x18 */ void *vtable;  /* PactNew sets each kind's own (game data) */
};

/* one entry of an act's vtable (delta, index, function, as g++ 2.95 lays them out) */
struct ACTVTENTRY {
    s16 delta;
    s16 index;
    void (*fn)(void *);
};

/* the vtable an act points at: slot 1 (entry at 0x08: ActivateActadj calls it), slot 4 (entry at 0x20: SeekAsega and
   RefreshXfActSegment call it without arguments when the clock leaves the transform's range) */
struct ACTVT {
    u8 unknown_0x0[0x8];
    /* 0x08 */ struct ACTVTENTRY slot1;
    /* 0x10 */ struct ACTVTENTRY slot2; /* reader: InsertXfAct, RemoveXfAct, ResortXfActList call it on the act that stops being the top one */
    /* 0x18 */ struct ACTVTENTRY slot3; /* reader: the same three call it on a top act that stays the top one */
    /* 0x20 */ struct ACTVTENTRY slot4;
};

/* an act's virtual call, as g++ 2.95 makes one: the entry's function on the act moved by the entry's delta. Slot 1 starts the
   act (it becomes the top one), slot 2 stops it (ActivateActadj, DeactivateActadj, ReselectActadj) */
static inline void CallActvtEntry(struct ACT *pact, const struct ACTVTENTRY *pentry)
{
    pentry->fn((char *)pact + pentry->delta);
}
static inline void CallActSlot1(struct ACT *pact)
{
    CallActvtEntry(pact, &((struct ACTVT *)pact->vtable)->slot1);
}
static inline void CallActSlot2(struct ACT *pact)
{
    CallActvtEntry(pact, &((struct ACTVT *)pact->vtable)->slot2);
}

struct ACTASEG {
    struct ACT act;
    /* 0x1C */ struct ASEGANIM *panim;      /* ApplyAseg stores the channel's curve here, or in panimAlt when its bit 31 is set */
    /* 0x20 */ struct ASEGANIM *panimAlt;
    /* 0x24 */ struct ASEGA *pasega;
    /* 0x28 */ struct ACTASEG *pactNext;
};

struct ACT1 {
    struct ACT act;
    /* 0x1C */ s32 field_0x1C;
    /* 0x20 */ QW vec20;           /* LoadAloFromBrx: the dof value at load time */
};

struct ACT2 {
    struct ACT act;
    u8 unknown_0x1C[0x4];
    /* 0x20 */ QW vec20;           /* LoadAloFromBrx: the dof value at load time */
    /* 0x30 */ struct CLQ clq30;   /* LoadAloFromBrx reads 12 bytes into each (func_00117F90), 8 into each range (func_00117FB0) */
    u8 unknown_0x3C[0x4];
    /* 0x40 */ struct CLQ clq40;
    u8 unknown_0x4C[0x4];
    /* 0x50 */ struct LM lm50;
    /* 0x58 */ struct LM lm58;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ s32 field_0x64;
    /* 0x68 */ s32 field_0x68;     /* LoadAloFromBrx copies it to the act's priority */
    /* 0x6C */ s32 field_0x6C;
    u8 unknown_0x70[0x10];
};

struct ACT4 {
    struct ACT act;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    u8 unknown_0x24[0x4];
};

struct ACT9 {
    struct ACT act;
    u8 unknown_0x1C[0x4];
    /* 0x20 */ struct VECTOR vec20; /* LoadAloFromBrx reads it with ReadVector */
};

struct ACTVAL {
    struct ACT act;
    /* 0x1C */ f32 tGoal;          /* the time the goal is reached: the jump code (StartJmpDirectionAseg_file) compares the clock with it */
    /* 0x20 */ QW posGoal;         /* SetActvalGoal */
    /* 0x30 */ QW velGoal;         /* SetActvalGoal; the jump code passes it back to SetActvalGoal */
};

#if defined(__mips__)
typedef char check_ACT_size[(sizeof(struct ACT) == 0x1C) ? 1 : -1];
typedef char check_ACT2_size[(sizeof(struct ACT2) == 0x80) ? 1 : -1];
typedef char check_ACTASEG_size[(sizeof(struct ACTASEG) == 0x2C) ? 1 : -1];
typedef char check_ACTVAL_size[(sizeof(struct ACTVAL) == 0x40) ? 1 : -1];
typedef char check_ACTVT_slot4[((unsigned int)&((struct ACTVT *)0)->slot4 == 0x20) ? 1 : -1];
#endif
#endif
