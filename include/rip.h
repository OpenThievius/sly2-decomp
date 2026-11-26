/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RIP, a particle ("rip"): 0xF0 bytes, its vtable pointer at 0xEC (not an LO: no vtable at 0xC; g++ puts it after the own
   fields). Subclasses (FLYING, STUCK, MATCH, GLINT, DROPLET, ...) add fields from 0xF0. RIPG is the group that owns them
   (class 87 of retail's class table, 0x1B0 bytes, derived from SO). A virtual is named after what its function does where
   a matched caller shows it, Slot<n> otherwise; a vtable entry is 8 bytes (delta, index, function), slot n at 8 * n.
   In C the same structs are plain, the vtable pointer an opaque field. C and C++. */
#ifndef SLY2_RIP_H
#define SLY2_RIP_H
#include "types.h"
#include "dl.h"
#include "emitter.h"
#ifdef __cplusplus
#include "so.h"
#else
struct SO;
#endif

struct LO;
struct RIPG;
struct ALO;

/* a quadratic c0 + u * (c1 + u * c2) in the ripple's age fraction u (FRenderRipPosMat) */
struct RIPQUADRATIC {
    f32 c0, c1, c2;
};

/* a subscriber of a RIP: a 0xC-byte slot of the heap at 0x3E1144; ReleaseRip sends each one's object message 8 */
struct RIPSUB {
    struct LO *plo;          /* readers: SubscribeRipObject (sets it), ReleaseRip */
    u8 unknown_0x4[0x4];
    struct RIPSUB *psubNext; /* the same two */
};

struct RIP {
    u8 unknown_0x0[0x4];
    /* 0x04 */ s32 cref;            /* readers: AddRipRef (++), ReleaseRip (--, frees at 0) */
    /* 0x08 */ struct RIPG *pripg;  /* reader: UpdateRip (its kind) */
    u8 unknown_0xC[0x8];
    /* 0x14 */ f32 tStart;          /* readers: UpdateRip, ForceRipFade, UpdateRipg, RenderRipgSelf, RenderMatch; InitRip sets it to now */
    /* 0x18 */ f32 dtLifetime;      /* readers: UpdateRip, ForceRipFade; InitRip sets 1.0 */
    /* 0x1C */ struct ALO *palo;   /* readers: FBounceLeaf (a LEAF passes it to CreateStuck), FRenderRipPosMat (reads its 0x38, an LO's radius, and renders it);
                                    TouchDroplet stores a word in it (a ripple's) */
#ifdef __cplusplus
    union {
        f32 field_0x20;             /* InitRip (its float argument); GLINT and MATCH reuse the offset */
        RIPQUADRATIC radius;        /* FRenderRipPosMat; TouchDroplet sets c0 (field_0x20) and c1 (30.0) of a ripple */
    };
    u8 unknown_0x2C[0x4];
    union {
        QW field_0x30;              /* InitRip, InitGlint, InitMatch set it from a constant */
        RIPQUADRATIC scale;         /* FRenderRipPosMat reads three floats of it */
    };
#else
    f32 field_0x20;
    u8 unknown_0x24[0xC];
    QW field_0x30;
#endif
    /* 0x40 */ QW field_0x40;       /* InitRip: the first three quadwords of a 0x2A2D00 table */
    /* 0x50 */ QW field_0x50;
    /* 0x60 */ QW field_0x60;
    /* 0x70 */ QW pos;              /* readers: UpdateRip (passed to SO slot 73), ProjectGlintTransform (kept in posPrev); InitRip sets it */
    /* 0x80 */ QW posPrev;          /* InitRip sets it to the position it gets; TouchDroplet reads it */
    u8 unknown_0x90[0x50];
    /* 0xE0 */ struct SO *psoTouch; /* readers: UpdateRip (pphys, grfo, slot 73); InitRip sets it to its SO argument */
    u8 unknown_0xE4[0x4];
    /* 0xE8 */ struct RIPSUB *psub; /* readers: ReleaseRip (frees each), SubscribeRipObject (pushes one) */
#ifdef __cplusplus
    virtual void Slot1(QW pos, float scale, int field); /*  1: a RIPPLE's start: TouchDroplet passes a position, a scale and 0 */
    virtual void Slot2();
    virtual void Release();                     /*  3: ReleaseRip calls it without arguments when the count reaches 0 */
    virtual void Slot4();
    virtual void Update();                      /*  5: UpdateRipg calls it on each RIP of its group, without arguments */
    virtual void Slot6();                       /*  6: RenderRipgSelf calls it on each RIP of its group, without arguments */
    virtual void Touch(int fTouching);          /*  7: UpdateRip passes whether the touched SO holds the position (TouchRip, TouchDroplet) */
#else
    void *vtable;                               /* 0xEC */
#endif
};

#if defined(__cplusplus) && defined(__mips__)
typedef char check_RIP_size[(sizeof(RIP) == 0xF0) ? 1 : -1];
#endif

/* RIP's constructor: the subclasses' constructors call it first with their own arguments (the name keeps retail's P6VECTOR,
   the position is passed as a quadword) */
#ifdef __cplusplus
extern "C"
#endif
void InitRip__FP3RIPP6VECTORfP2SO(struct RIP *rip, QW pos, float field_0x20, struct SO *psoTouch);

/* the group of RIPs: a SO that keeps its RIPs in a DL */
#ifdef __cplusplus
struct RIPG : SO {
#else
struct RIPG {
    u8 unknown_0x0[0x150]; /* an SO in C++ */
#endif
    /* 0x150 */ s32 kind;       /* readers: UpdateRip (through RIP::pripg), func_001CE6C0 (tests it against 1) */
    u8 unknown_0x154[0x4];
    /* 0x158 */ f32 field_0x158; /* SetRipgEmitb copies it from the emitter's 0xD4 */
    /* 0x15C */ struct DL rips;  /* UpdateRipg, RenderRipgSelf iterate it */
    u8 unknown_0x168[0x48];
};

#endif
