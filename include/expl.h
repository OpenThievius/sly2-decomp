/* SPDX-License-Identifier: GPL-3.0-or-later */
/* EXPL, an explosion: class 30 of retail's class table (0x2BAAE8, config/recovered/class_diff.tsv), derived from XFM (class 3,
   include/xfm.h) without fields of its own (0xE0 bytes). Its one new virtual is slot 51, ExplodeExplso, which takes an EXPLSO
   (the description of one explosion, 0x40 bytes). Retail's vtables fill it as follows: EXPL's own table (0x2CE9D0) and EXPLO's
   (class 32, 0x2CA098) with ExplodeExplExplso (empty), EXPLG's (class 31, 0x2CE828) with ExplodeExplgExplso, EXPLS's (class 33,
   0x2CE4D0) with ExplodeExplsExplso, which calls EXPLS's own slot 52, FireExplsExplso. Callers of slot 51: ExplodeExpl,
   ExplodeExplParams, UpdateRemit (rip), DetonateBomb (BOMB::pbombOther), FAbsorbSlotSoWkr (SLOTSO::field_0x1C8).
   EXPLG (class 31) is left to its source (InitEmitb_file.cpp holds a local EXPLG). The names EXPL, EXPLS and EXPLSO are retail's
   mangled ones (ExplodeExplParams__FP4EXPL..., FireExplsExplso__FP5EXPLSP6EXPLSO). C++ only. */
#ifndef SLY2_EXPL_H
#define SLY2_EXPL_H
#include "xfm.h"

struct ALO;
struct XFR;
struct EMITB;

/* what to explode with: grfexpl says which of the fields count (FireExplsExplso: 1 palo, 2 vec, 4 pos, 8 and 0x10 g/uPercent,
   0x20 field_0x30, 0x40 pxfr, 0x80 cparticle) */
struct EXPLSO {
    /* 0x00 */ u32 grfexpl;      /* FireExplsExplso; UpdateRemit sets 4, FAbsorbSlotSoWkr 6, DetonateBomb 9 */
    /* 0x04 */ struct ALO *palo; /* FireExplsExplso (grfexpl & 1: the emitter's object); ExplodeExplParams, DetonateBomb set it */
    /* 0x08 */ f32 g;            /* FireExplsExplso (grfexpl & 8 and 0x10: the particle-count and speed scale); ExplodeExplParams, DetonateBomb */
    /* 0x0C */ f32 uPercent;     /* FireExplsExplso (the scale in percent when g is 0); ExplodeExplParams, DetonateBomb */
    /* 0x10 */ QW vec;           /* FireExplsExplso (grfexpl & 2: the emit block's vector); ExplodeExplParams, FAbsorbSlotSoWkr (WKR::vel) */
    /* 0x20 */ QW pos;           /* FireExplsExplso (grfexpl & 4: the emit position); ExplodeExplParams, UpdateRemit, FAbsorbSlotSoWkr (WKR::pos) */
    /* 0x30 */ s32 field_0x30;   /* FireExplsExplso (grfexpl & 0x20: copied into the emit origin) */
    /* 0x34 */ struct XFR *pxfr; /* FireExplsExplso (grfexpl & 0x40: the emit block's transform) */
    /* 0x38 */ s32 cparticle;    /* FireExplsExplso (grfexpl & 0x80: replaces the random particle count) */
    u8 unknown_0x3C[0x4];
};

struct EXPL : XFM {
    virtual void ExplodeExplso(EXPLSO *pexplso); /* 51: ExplodeExplExplso, ExplodeExplgExplso, ExplodeExplsExplso */
};

/* class 32, 0xF0 bytes: LoadExploFromBrx is its loader (slot 15) */
struct EXPLO : EXPL {
    u8 unknown_0xE0[0x4];
    /* 0xE4 */ struct EMITB *pemitb; /* LoadExploFromBrx allocates and loads it; FireExplsExplso copies it */
    u8 unknown_0xE8[0x8];
};

/* class 33, 0x110 bytes */
struct EXPLS : EXPLO {
    virtual void FireExplso(EXPLSO *pexplso); /* 52: FireExplsExplso; ExplodeExplsExplso calls it */
    u8 unknown_0xF0[0x10];
    /* 0x100 */ void *pripg;  /* HandleExplsMessage (clears it when it goes away), FireExplsExplso (hands its address to the emitter) */
    /* 0x104 */ void *pblipg; /* HandleExplsMessage, FireExplsExplso, likewise */
    u8 unknown_0x108[0x8];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(EXPLSO, 0x40);
SLY2_OFFSET_CHECK(EXPLSO, pos, 0x20);
SLY2_OFFSET_CHECK(EXPLSO, cparticle, 0x38);
SLY2_SIZE_CHECK(EXPL, 0xE0);
SLY2_SIZE_CHECK(EXPLO, 0xF0);
SLY2_OFFSET_CHECK(EXPLO, pemitb, 0xE4);
SLY2_SIZE_CHECK(EXPLS, 0x110);
SLY2_OFFSET_CHECK(EXPLS, pripg, 0x100);
#endif
#endif
