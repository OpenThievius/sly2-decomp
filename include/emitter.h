/* SPDX-License-Identifier: GPL-3.0-or-later */
/* EMITTER and its emit block EMITB (retail's name, from SetRipgEmitb__FP4RIPGP5EMITB). An EMITTER keeps a pointer to a shared,
   copy-on-write EMITB at 0xE4 (PemitbEnsureEmitter copies it when its reference count is 2 or more; OnEmitterValuesChanged hands the
   same word to SetRipgEmitb and SetBlipgEmitb). The *Emitter* functions of src/new_258658/ and their twins in src/suv-end/ read the
   EMITTER and its block; the RIP callbacks of src/rip/ (SetRipgEmitb, PostFlyingEmit, PostDropletEmit, PostRemitEmit) receive the block
   itself. Fields come from the matched functions that read them at those offsets. C and C++. */
#ifndef SLY2_EMITTER_H
#define SLY2_EMITTER_H
#include "types.h"
#include "sly2.h"

struct LO;
struct EMITMESH;
struct XFR;

/* One parameter block of an EMITB, 16-byte aligned: a kind word, then the payload at +0x30 (the func_002596F8 family returns
   &payload when the kind matches). */
struct EMITPARAMS {
    /* 0x00 */ s32 kind;
    union {
        /* 0x4 */ s32 blipmk;   /* EMITB 0xC4, the blip kind: EmitParticles (2: the spline sink) */
        s32 ripgt;               /* EMITB 0xC4, the rip kind: EmitRips (the group's type) */
    };
    /* 0x8 */ s32 oidA;         /* EMITB 0xC8: PostSuvLoad (SUV slot 15) and BindEmitter (emitpk 1): the object ids of a kind-1 block */
    union {
        /* 0xC */ s32 oidB;     /* EMITB 0xCC: PostSuvLoad, BindEmitter (emitpk 1) */
        s32 colorRanges;        /* EMITB 0xCC, the blip kind: LoadEmitblipColors and LoadEmitblipColorsFromBrx store the number of colour ranges */
    };
    /* 0x10 */ s32 oidC;        /* EMITB 0xD0: PostSuvLoad, BindEmitter */
    union {
        f32 field_0x14;         /* EMITB 0xD4: SetRipgEmitb copies it to the group */
        s32 oidSpline;          /* EMITB 0xD4: PostSuvLoad and BindEmitter (emitpk 0), for a kind-0 block */
    };
    /* 0x18 */ f32 gMin;        /* EMITB 0xD8, the rip kind: EmitRips (the particle scale range), FireExplsExplso (gD8, set from EXPLSO::g) */
    union {
        /* 0x1C */ s32 *table;  /* EMITB 0xDC, the blip kind: LoadEmitblipColors and LoadEmitblipColorsFromBrx allocate it (a count word, then the colours) */
        f32 gMax;                /* EMITB 0xDC, the rip kind: EmitRips, FireExplsExplso (gDC) */
    };
    /* 0x20 */ struct VECTOR vecScale; /* EMITB 0xE0: FireExplsExplso scales it for a blip-kind block (EmitRips reads the rip kind's words at 0x24
                                          and 0x28 through its own view: one reader) */
    /* 0x30 */ s32 payload;     /* EMITB 0xF0: PostFlyingEmit and PostRemitEmit read its first word */
    /* 0x34 */ f32 field_0x34;  /* EMITB 0xF4: PostRemitEmit */
    u8 unknown_0x38[0x8];
} __attribute__((aligned(16)));

struct EMITV { QW q[7]; };    /* 0x70 bytes: EMITB 0x50, copied as one block by InitEmitb and EmitRipsSphere */
struct EMITRIP { QW q[4]; };  /* 0x40 bytes: EMITB 0xC0, the params block copied by EmitRipsSphere */
struct EMITBBOX { f32 minX, minY, minZ, minW, maxX, maxY, maxZ, maxW; };

/* an object a kind-2 EMITB follows: its +0xF4 points at a position */
struct EMITOBJ {
    u8 unknown_0x0[0xF4];
    /* 0xF4 */ QW *ppos;        /* FireExplsExplso (emitk 2) */
};

/* what EMITB::pinfo points at (0x14 bytes: CEmitter_PostLoad and FireExplsExplso copy them) */
struct EMITBINFO {
    /* 0x0 */ struct LO *plo;   /* PostRemitEmit: the object it looks its target up from; CEmitter_PostLoad (tests and clears it), UpdateEmitter (the owner), ModifyEmitterParticles, FireExplsExplso (EXPLSO::palo), AttachEmitterToReference */
    /* 0x4 */ struct EMITOBJ *pobj; /* FireExplsExplso (emitk 2), UpdateEmitter (tests it before taking the emitter as the owner; guess) */
    u8 unknown_0x8[0x4];        /* EmitRips copies a word from here into the particle (one reader: its own view) */
    /* 0xC */ s32 field_0xC;    /* PostFlyingEmit, PostDropletEmit */
    /* 0x10 */ s32 field_0x10;  /* EmitRips (passed to the particle's Init), FireExplsExplso (EXPLSO::field_0x30 goes here) */
};

/* what an emitter hands EmitParticles: where to keep the groups it creates (UpdateEmitter, FireExplsExplso, EmitRips, EmitRipsSphere) */
struct EMITG {
    /* 0x0 */ struct BLIPG **ppblipg;
    /* 0x4 */ struct RIPG **ppripg;
    /* 0x8 */ struct LO *plo;
};

/* the emit block: 0x100 bytes, copy-on-write when cref >= 2 (PemitbEnsureEmitter, func_002590F0) */
struct EMITB {
    /* 0x00 */ s32 cref;                /* PemitbEnsureEmitter, func_002590F0 */
    /* 0x04 */ s32 emitpk;              /* which parameter block is in use (0 blip, 1 rip): PemitripEnsureEmitter, PemitblipEnsureEmitter, EmitParticles, UpdateEmitter, ModifyEmitterParticles */
    /* 0x08 */ struct EMITBINFO *pinfo; /* PostFlyingEmit, PostDropletEmit, PostRemitEmit; CEmitter_PostLoad (copies it, 0x14 bytes), UpdateEmitter, ModifyEmitterParticles */
    u8 unknown_0xC[0x4];
    /* 0x10 */ s32 emitok;              /* SetEmitterEmitok; CEmitter_PostLoad (1: a box), FireExplsExplso (emitk, 0..3: the position kind) */
    u8 unknown_0x14[0x8];
    /* 0x1C */ struct XFR *pxfr;        /* FireExplsExplso (EXPLSO::pxfr goes here; the position is rotated by it) */
    /* 0x20 */ s32 oidReference;        /* PostSuvLoad (SUV slot 15), BindEmitter: the object the emitter follows (the first entry of pinfo's pointers); CEmitter_PostLoad */
    u8 unknown_0x24[0xC];
    union {
        /* 0x30 */ s32 field_0x30;      /* SetEmitterEmitok writes it, func_00258B00 and func_00259598 read it */
        s32 oidCurve;                    /* BindEmitter: the curve, looked up when emitok is 2 */
        struct EMITMESH *pemitmesh;      /* LoadEmitterFromBrx hands it to LoadEmitmeshFromBrx when emitok is 3 */
        struct EMITBBOX *pbox;           /* CEmitter_PostLoad (emitok 1) */
        QW pos;                          /* FireExplsExplso (emitok 0), EmitRipsSphere */
        QW *apos;                        /* FireExplsExplso (emitok 1 and 3: an array of positions) */
        char *pb;                        /* FireExplsExplso */
    };
    /* 0x40 */ QW vec;                  /* FireExplsExplso (EXPLSO::vec), EmitRipsSphere */
    union {
        /* 0x50 */ struct EMITV emitv;  /* InitEmitb and EmitRipsSphere copy it as a block */
        struct { f32 gMin, gMax; } lmSpeed; /* FireExplsExplso: the speed range, scaled by EXPLSO::g */
    };
    union {
        /* 0xC0 */ struct EMITPARAMS params;
        struct EMITRIP emitrip;          /* EmitRipsSphere copies the block */
    };
};

#ifdef __cplusplus
#include "xfm.h"
#include "dl.h"
#include "bytes8.h"
struct RIPG;
struct BLIPG;

/* an emitter: an XFM (0xE0 bytes) with its own words from 0xE0. Readers are the functions of src/dzg-emitter/InitEmitb_file.cpp
   (several agree on each offset; CEmitter_PostLoad is the class's slot 15). */
struct EMITTER : XFM {
    /* 0xE0 */ s32 ensured;             /* PemitbEnsureEmitter; OnEmitterValuesChanged clears it, SetEmitterEnabled and func_0015A2B0 set it, UpdateEmitter tests it */
    /* 0xE4 */ struct EMITB *pemitb;    /* PemitbEnsureEmitter, OnEmitterValuesChanged and the getters; CEmitter_PostLoad, UpdateEmitter, ModifyEmitterParticles */
    u8 unknown_0xE8[0x8];
    /* 0xF0 */ s32 emitk;               /* the emission mode (-1 unset, 0..3): CEmitter_PostLoad, UpdateEmitter, OnEmitterValuesChanged, SetEmitterEnabled, FPausedEmitter, InitEmitter */
    /* 0xF4 */ s32 cParticlesLeft;      /* -1 unlimited: UpdateEmitter; SetEmitterEnabled stores the enabled count, FPausedEmitter, CEmitter_PostLoad, InitEmitter */
    union {
        BYTES8 bytesRate;                /* CEmitter_PostLoad copies the pair as eight bytes */
        struct { f32 gMin, gMax; } lmRate; /* the range of rate: OnEmitterValuesChanged, UpdateEmitter, CEmitter_PostLoad, InitEmitter (both 10.0) */
    };
    /* 0x100 */ s32 field_0x100;        /* CEmitter_PostLoad (the class's slot 15, a method; nonzero: scales the density by the box) */
    /* 0x104 */ f32 uPause;             /* the chance to pause: UpdateEmitter, CEmitter_PostLoad */
    union {
        BYTES8 bytesPause;               /* CEmitter_PostLoad copies the pair as eight bytes */
        struct { f32 gMin, gMax; } lmPause; /* the pause time range: UpdateEmitter, CEmitter_PostLoad */
    };
    /* 0x110 */ f32 cMax;               /* UpdateEmitter (mode 1), CEmitter_PostLoad (nonzero picks mode 1) */
    /* 0x114 */ s32 fPauseIndefinite;   /* UpdateEmitter, CEmitter_PostLoad */
    /* 0x118 */ s32 oidTarget;          /* the object id of the second emitter (-1 none): CEmitter_PostLoad, UpdateEmitter, InitEmitter */
    /* 0x11C */ struct DL dlSrc;        /* the source list, ibDle 0x128: InitEmitter (InitDl), UpdateEmitter, CEmitter_PostLoad (AppendDlEntry) */
    u8 unknown_0x128[0x8];
    /* 0x130 */ f32 rate;               /* OnEmitterValuesChanged, UpdateEmitter, CEmitter_PostLoad */
    /* 0x134 */ f32 dtReset;            /* UpdateEmitter, CEmitter_PostLoad (sets 1.0) */
    /* 0x138 */ f32 tReset;             /* UpdateEmitter, CEmitter_PostLoad */
    /* 0x13C */ f32 svRate;             /* UpdateEmitter, CEmitter_PostLoad */
    /* 0x140 */ f32 sRadius;            /* ModifyEmitterParticles, CEmitter_PostLoad */
    /* 0x144 */ f32 fracParticles;      /* UpdateEmitter */
    /* 0x148 */ f32 tUnpause;           /* PauseEmitter, PauseEmitterIndefinite, UnpauseEmitter, FPausedEmitter, InitEmitter */
    /* 0x14C */ struct RIPG *pripg;     /* the ripple group the emitter feeds: UpdateEmitter, OnEmitterValuesChanged, HandleEmitterMessage */
    /* 0x150 */ struct BLIPG *pblipg;   /* the blip group: UpdateEmitter, OnEmitterValuesChanged, HandleEmitterMessage, ModifyEmitterParticles */
};
#else
struct EMITTER {
    u8 unknown_0x0[0xE0];
    /* 0xE0 */ s32 ensured;             /* PemitbEnsureEmitter; OnEmitterValuesChanged clears it */
    /* 0xE4 */ struct EMITB *pemitb;    /* PemitbEnsureEmitter, OnEmitterValuesChanged and the getters */
};
#endif

#if defined(__mips__)
typedef char check_EMITB_size[(sizeof(struct EMITB) == 0x100) ? 1 : -1];
typedef char check_EMITB_params[((unsigned int)&((struct EMITB *)0)->params == 0xC0) ? 1 : -1];
#endif
#endif
