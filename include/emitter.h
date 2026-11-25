/* SPDX-License-Identifier: GPL-3.0-or-later */
/* EMITTER and its emit block EMITB (retail's name, from SetRipgEmitb__FP4RIPGP5EMITB). An EMITTER keeps a pointer to a shared,
   copy-on-write EMITB at 0xE4 (PemitbEnsureEmitter copies it when its reference count is 2 or more; OnEmitterValuesChanged hands the
   same word to SetRipgEmitb and SetBlipgEmitb). The *Emitter* functions of src/new_258658/ and their twins in src/suv-end/ read the
   EMITTER and its block; the RIP callbacks of src/rip/ (SetRipgEmitb, PostFlyingEmit, PostDropletEmit, PostRemitEmit) receive the block
   itself. Fields come from the matched functions that read them at those offsets. C and C++. */
#ifndef SLY2_EMITTER_H
#define SLY2_EMITTER_H
#include "types.h"

struct LO;
struct EMITMESH;

/* One parameter block of an EMITB, 16-byte aligned: a kind word, then the payload at +0x30 (the func_002596F8 family returns
   &payload when the kind matches). */
struct EMITPARAMS {
    /* 0x00 */ s32 kind;
    u8 unknown_0x4[0x4];
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
    u8 unknown_0x18[0x4];
    /* 0x1C */ s32 *table;      /* EMITB 0xDC, the blip kind: LoadEmitblipColors and LoadEmitblipColorsFromBrx allocate it (a count word, then the colours) */
    u8 unknown_0x20[0x10];
    /* 0x30 */ s32 payload;     /* EMITB 0xF0: PostFlyingEmit and PostRemitEmit read its first word */
    /* 0x34 */ f32 field_0x34;  /* EMITB 0xF4: PostRemitEmit */
    u8 unknown_0x38[0x8];
} __attribute__((aligned(16)));

/* what EMITB::pinfo points at: only what two RIP callbacks read */
struct EMITBINFO {
    /* 0x0 */ struct LO *plo;   /* PostRemitEmit: the object it looks its target up from */
    u8 unknown_0x4[0x8];
    /* 0xC */ s32 field_0xC;    /* PostFlyingEmit, PostDropletEmit */
};

/* the emit block: 0x100 bytes, copy-on-write when cref >= 2 (PemitbEnsureEmitter, func_002590F0) */
struct EMITB {
    /* 0x00 */ s32 cref;                /* PemitbEnsureEmitter, func_002590F0 */
    /* 0x04 */ s32 emitpk;              /* which parameter block is in use: PemitripEnsureEmitter, PemitblipEnsureEmitter */
    /* 0x08 */ struct EMITBINFO *pinfo; /* PostFlyingEmit, PostDropletEmit, PostRemitEmit */
    u8 unknown_0xC[0x4];
    /* 0x10 */ s32 emitok;              /* SetEmitterEmitok */
    u8 unknown_0x14[0xC];
    /* 0x20 */ s32 oidReference;        /* PostSuvLoad (SUV slot 15), BindEmitter: the object the emitter follows (the first entry of pinfo's pointers) */
    u8 unknown_0x24[0xC];
    union {
        /* 0x30 */ s32 field_0x30;      /* SetEmitterEmitok writes it, func_00258B00 and func_00259598 read it */
        s32 oidCurve;                    /* BindEmitter: the curve, looked up when emitok is 2 */
        struct EMITMESH *pemitmesh;      /* LoadEmitterFromBrx hands it to LoadEmitmeshFromBrx when emitok is 3 */
    };
    u8 unknown_0x34[0x8C];
    /* 0xC0 */ struct EMITPARAMS params;
};

struct EMITTER {
    u8 unknown_0x0[0xE0];
    /* 0xE0 */ s32 ensured;             /* PemitbEnsureEmitter; OnEmitterValuesChanged clears it */
    /* 0xE4 */ struct EMITB *pemitb;    /* PemitbEnsureEmitter, OnEmitterValuesChanged and the getters */
};

#if defined(__mips__)
typedef char check_EMITB_size[(sizeof(struct EMITB) == 0x100) ? 1 : -1];
typedef char check_EMITB_params[((unsigned int)&((struct EMITB *)0)->params == 0xC0) ? 1 : -1];
#endif
#endif
