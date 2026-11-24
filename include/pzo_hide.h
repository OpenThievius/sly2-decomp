/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The types of src/pzo-hide/ (C and C++): the MEMBER block that the Attach* classes carry, and the three Attach* classes.
   MEMBER: a sub-object with its vtable pointer at 0x20 (Member_GetRandomPos, Member_GetPosNearJt read it; a vtable entry is
   delta, index, function). The Attach* classes hold it at +0xE0 (Cyl, Flat) or +0x190 (Crv), and their overrides of MEMBER's
   slots (AttachCrv_FGetWrapRange, AttachCyl_GetRandomPos) receive the whole object: the entry's delta is minus that offset.
   In C the vtable is a plain struct; in C++ the same bytes are virtuals, called as methods. */
#ifndef SLY2_PZO_HIDE_H
#define SLY2_PZO_HIDE_H
#include "types.h"
#include "dl.h"
#include "clock.h"
#include "bytes8.h"
#include "rsmg.h"
#ifdef __cplusplus
#include "sohit.h"
#endif

#ifdef __cplusplus
struct MEMBER {
    /* 0x0 */ s32 field_0x0;   /* reader: SetJtPipeState (a PIPE's word at 0x190, passed to func_00140C88) */
    u8 unknown_0x4[4];
    /* 0x8 */ f32 field_0x8;   /* InitCtrlBlock_182c70 (bevy_player_p6_182c70): FLT_MAX; a method of the class, so certain */
    /* 0xC */ s32 field_0xC;  /* reader: UpdateJtPipeLook (tests it for 0 before adding a safe point) */
    /* 0x10 */ s32 field_0x10; /* AttachPt_Init (1) and LiftPt_Init (-1) set it, after the base constructor */
    /* 0x14 */ s32 field_0x14; /* the same: -1 */
    u8 unknown_0x18[4];
    /* 0x1C */ s32 field_0x1C; /* the same: 7 */
    /* 0x20: the vtable pointer */
    virtual int FGetWrapRange(f32 *range); /* 1: Member_FGetWrapRange; AttachCrv_FGetWrapRange fills {min, max} and returns 1 */
    virtual void GetParam(void *joint, f32 *param); /* 2: Member_GetParam; Member_GetPosNearJt passes a joint and the result's address */
    virtual void GetPosFromParam(f32 param, void *joint, void *position, f32 *heading); /* 3: Member_GetPosFromParam */
    virtual void GetPosNearJt(void *joint, f32 *param, void *position, f32 *heading);   /* 4: Member_GetPosNearJt */
    virtual void Slot5();                  /* 5: Member_Slot20 (empty) */
    virtual void *Slot6();                 /* 6: Member_GetRandomPos reads the owner's LO from it */
};
#else
struct MEMBERVT {
    u8 unknown_0x0[0x30];
    /* 0x30 */ s16 delta;
    /* 0x32 */ s16 index;
    /* 0x34 */ void *(*fn)(void *);
};
struct MEMBER {
    u8 unknown_0x0[8];
    /* 0x8 */ f32 field_0x8;
    u8 unknown_0xC[4];
    /* 0x10 */ s32 field_0x10;
    /* 0x14 */ s32 field_0x14;
    u8 unknown_0x18[4];
    /* 0x1C */ s32 field_0x1C;
    /* 0x20 */ const struct MEMBERVT *vt;
};
#endif


/* a curve attachment: a CRV (InitCrv, CloneCrv, SMinCrv, SMaxCrv) with a MEMBER at +0x190 */
struct ATTACHCRV {
    u8 unknown_0x0[0xE4];
    /* 0xE4 */ s32 closed;         /* AttachCrv_FGetWrapRange (a wrap range only when closed? it returns 0 when 0), AttachCrv_GetParam */
    u8 unknown_0xE8[0x190 - 0xE8];
    /* 0x190 */ struct MEMBER member;
    /* 0x1B4 */ struct BYTES8 kept; /* AttachCrv_Clone */
    /* 0x1BC */ s32 field_0x1BC;  /* AttachCrv_Init sets 3 (a method of the class: one reader is enough) */
};

/* a cylinder attachment: an XFM (InitXfm, CloneXfm) with a MEMBER at +0xE0 */
struct ATTACHCYL {
    u8 unknown_0x0[0xE0];
    /* 0xE0 */ struct MEMBER member;
    /* 0x104 */ struct BYTES8 kept; /* AttachCyl_Clone */
    /* 0x10C */ f32 heightOffset;   /* AttachCyl_GetRandomPos adds it to the random height; AttachCyl_PostLoad reads it as the radius */
};

/* a flat attachment: an XFM with a MEMBER at +0xE0 */
struct ATTACHFLAT {
    u8 unknown_0x0[0xE0];
    /* 0xE0 */ struct MEMBER member;
    /* 0x104 */ struct BYTES8 kept; /* AttachFlat_Clone */
};

/* an attach point: an XFM with a MEMBER at +0xE0 (the constructor func_00183F08 is InitXfm, the member's, then three stores; AttachPt_OnAdd and
   AttachPt_OnRemove keep it in B_003E1414) */
struct ATTACHPT {
    u8 unknown_0x0[0xE0];
    /* 0xE0 */ struct MEMBER member;
    u8 unknown_0x104[0xC];
    /* 0x110 */ f32 field_0x110;   /* the constructor sets 200.0 */
};

/* an object id and what PloFindSwObject finds for it (func_001842B0 fills three of them from their ids) */
struct OIDREF {
    s32 oid;
    void *plo;
};

/* a lift point, an ATTACHPT (its constructor func_00184268 calls the AttachPt one; LiftPt_OnGrab hands the grabber to StartMurrayLift) */
struct LIFTPT {
    struct ATTACHPT attachpt;
    u8 unknown_0x114[0x6C];
    /* 0x180 */ s32 field_0x180;   /* func_00184380 passes it to func_001A6AF8 */
    /* 0x184 */ struct OIDREF aref[3]; /* func_00184268 clears the ids (-1), func_001842B0 resolves them */
    /* 0x19C */ s32 oidLast;       /* func_00184268 (-1), func_00184380 compares it with the other object's member.field_0x14 */
};

/* an attach zone: an XFM with a MEMBER at +0x130 (the constructor func_001843C0; AttachZone_OnAdd and AttachZone_OnRemove keep it in B_003E1438) */
struct ATTACHZONE {
    u8 unknown_0x0[0x130];
    /* 0x130 */ struct MEMBER member;
};

/* One animation entry of a SOHIT subclass (0x10 bytes): SoHit_SetAnimEntry (func_0017F4C0) plays aseg and sm with flags; Chaser_SetStateAnim and
   Grab_SetStateAnim write oid and flags; ClearOidEntries (func_0017F3E0) sets oid to -1; ResolveOidEntries (func_0017F408) fills aseg and sm
   from the object found by oid */
struct ANIMENTRY {
    /* 0x0 */ s32 oid;
    /* 0x4 */ void *aseg;
    /* 0x8 */ void *sm;
    /* 0xC */ u32 flags;
};

/* RSMG, a rule state machine record: rsmg.h */

/* GRAB (class 75 by Grab_Init's role, guessed from state 1 handing an anchor to the player: decomp_names.md), a SOHIT (0x1C0 bytes,
   sohit.h): its fields from 0x1C0. In C (the C files of this module) SOHIT does not exist: the same fields follow 0x1C0 bytes of unknown. Readers: Grab_Reset (func_00181598),
   Grab_SetState (func_001815E8), Grab_FAddRsmg (func_001816E8), Grab_ReleasePlayer (func_00181728), Grab_Init, Grab_PostLoad (both methods). */
#define GRAB_FIELDS \
    s32 state;                  /* 0x1C0: Grab_SetState; the same slot holds Mount's and Chaser's state */ \
    f32 tState;                 /* 0x1C4: the clock at the last state change */ \
    struct MOUNT *pmount;       /* 0x1C8: Grab_SetState, Grab_ReleasePlayer: an object it passes to Mount_SetState (a MOUNT, whose field 0x294 it sets) */ \
    void *anchor;               /* 0x1CC: Grab_SetState stores it in the mount */ \
    struct ANIMENTRY aentry[3]; /* 0x1D0: Grab_Init, Grab_PostLoad (the methods that clear and resolve three entries) */ \
    s32 crsmg;                  /* 0x200: Grab_FAddRsmg's count (at most 4), Grab_Reset */ \
    struct RSMG arsmg[4];       /* 0x204: Grab_FAddRsmg passes the array and a maximum of 4 */

#ifdef __cplusplus
#include "clock.h"
#include "bytes8.h"
#include "mount.h"
#include "sw.h"

struct GRAB : SOHIT {
    GRAB_FIELDS
};

/* CHASER, a SOHIT (Chaser_SetState, Chaser_SetStateDistanceRanges, Chaser_SetStateAngleRanges, Chaser_FTakeHit are its methods). Per state
   (five) an animation entry at 0x220 and a range record at 0x270 whose two halves the two setters fill: the 8-byte pairs are passed by pointer
   and copied whole, their type is not known. */
struct CRV;
struct CHASERRANGE {
    s32 fDistance;          /* 0x0: Chaser_SetStateDistanceRanges sets it to 1 */
    s32 fAngle;             /* 0x4: Chaser_SetStateAngleRanges sets it to 1 */
    BYTES8 distanceMin;     /* 0x8 */
    BYTES8 distanceMax;     /* 0x10 */
    BYTES8 angleMin;        /* 0x18 */
    BYTES8 angleMax;        /* 0x20 */
};

struct CHASER : SOHIT {
    /* 0x1C0 */ s32 state;   /* Chaser_SetState (-1 before the first); Chaser_FTakeHit */
    /* 0x1C4 */ f32 tState;  /* Chaser_SetState: the clock at the change */
    u8 unknown_0x1C8[0x10];
    /* 0x1D8 */ struct CRV *pcrv; /* Chaser_PostLoad: PcrvNew(0x2C9, 0x10) */
    u8 unknown_0x1DC[0x34];
    /* 0x210 */ s32 field_0x210[3]; /* Chaser_SetState clears these three words for states 0 to 2 and 4 (a vector, probably) */
    u8 unknown_0x21C[4];
    /* 0x220 */ ANIMENTRY aentry[5];  /* Chaser_SetState plays the entry of the new state; Chaser_SetStateAnim */
    /* 0x270 */ CHASERRANGE arange[5];
    /* 0x338 */ f32 field_0x338;    /* Chaser_Init sets 250.0 */
    u8 unknown_0x33C[0x4];
    /* 0x340 */ f32 field_0x340;    /* Chaser_Init sets 1.0 */
    u8 unknown_0x344[0xC];
    /* 0x350 */ f32 field_0x350;    /* Chaser_Init sets 1.0 */
    u8 unknown_0x354[0x10];
    /* 0x364 */ f32 field_0x364;    /* Chaser_Init sets 1.0 */
    u8 unknown_0x368[0x8];
    /* 0x370 */ f32 field_0x370;    /* Chaser_Init sets -FLT_MAX */
    /* 0x374 */ f32 field_0x374;    /* Chaser_Init sets FLT_MAX */
};

/* a Swarm rider (0x64+ bytes; the swarm keeps them in its groups' lists and its dead list, linked through the DLE at 0x60) */
struct SWARMRIDER {
    u8 unknown_0x0[0x20];
    /* 0x20 */ struct SWARMGROUP *group; /* Swarm_Reset, Swarm_SetRiderState */
    /* 0x24 */ s32 state;                /* Swarm_SetRiderState (2 = dead) */
    /* 0x28 */ f32 tState;               /* the clock at the change */
    u8 unknown_0x2C[0x34];
    /* 0x60 */ DLE dle;                  /* Swarm_Reset: the dead list's entry (InitDl's ibDle 0x60) */
};

struct SWARMGROUP {
    u8 unknown_0x0[4];
    /* 0x4 */ s32 total;  /* Swarm_Reset: alive is reset to it */
    u8 unknown_0x8[4];
    /* 0xC */ s32 alive;  /* Swarm_Reset, Swarm_SetRiderState */
    /* 0x10 */ DL dl;     /* the group's live riders: Swarm_SetRiderState removes a dying one */
    u8 unknown_0x1C[0x14];
};

/* SWARM, a SOHIT: up to four groups, a dead list */
struct SWARM : SOHIT {
    u8 unknown_0x1C0[0x8];
    /* 0x1C8 */ s32 cgroup;            /* Swarm_Reset */
    /* 0x1CC */ SWARMGROUP agroup[4];  /* Swarm_Reset (indexes it), Swarm_AbsorbTouch's Swarm_182AB8 agrees on 4 */
    /* 0x28C */ DL dlDead;             /* Swarm_Init: InitDl(&dlDead, 0x60); Swarm_Reset empties it; Swarm_SetRiderState appends */
};
#else
struct GRAB {
    u8 unknown_0x0[0x1C0];
    GRAB_FIELDS
};
#endif

/* the three lists of attachments by kind (OnAdd appends, OnRemove removes) */
extern struct DL B_003E13F0; /* ATTACHCRV */
extern struct DL B_003E13FC; /* ATTACHCYL */
extern struct DL B_003E1408; /* ATTACHFLAT */
extern struct DL B_003E1414; /* ATTACHPT */
extern struct DL B_003E1438; /* ATTACHZONE */
#endif
