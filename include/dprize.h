/* SPDX-License-Identifier: GPL-3.0-or-later */
/* DPRIZE, the dropped prize of src/new_1c3df8/ (InitDprize, LoadDprizeFromBrx, PostDprizeLoad, CheckDprizeCollect, UpdateDprize,
   RenderDprizeAll, SetDprizeDprizes, HandleDprizeMessage and the Coin, Charm and Key variants): an SO (0x150 bytes, include/so.h).
   Its vtable adds slot 76 (offset 0x260), which every caller reaches with a state: SetDprizes (SetDprizeCoinDprizes,
   SetDprizeCharmDprizes and SetDprizeKeyDprizes are the three overrides; the base SetDprizeDprizes sets the state itself). The state
   field keeps that name, as HBSK's hbsks does. Names follow config/recovered/decomp_names.md; every field is read by a method of the
   class or by two functions that agree. The three variants differ from 0x230 (the base is 0x230 bytes); each one is a local subclass.
   The record SMA, the message SMAMSG and the message sink MSGSINK are local views: one class each is not recovered. C++ only. */
#ifndef SLY2_DPRIZE_H
#define SLY2_DPRIZE_H
#include "sly2.h"
#include "rows3.h"
#include "so.h"
#include "asega.h"
#include "sma.h"


/* the data of message 10 (an SMA event) that HandleDprizeMessage reads */
struct SMAMSG {
    /* 0x0 */ struct SMA *psma;
    u8 unknown_0x4[0x4];
    /* 0x8 */ s32 event; /* 0x186: the prize's own animation ended */
};

/* what a prize's collect and expire hooks are: an object whose slot 51 (offset 0x198) takes a message {1, source}; its class is not
   recovered, so the vtable is read by hand (entry: delta, index, function) */
struct MSGSINKVT {
    u8 unknown_0x0[0x198];
    s16 delta;
    s16 index;
    void (*fn)(void *, int *);
};
struct MSGSINK {
    u8 unknown_0x0[0xC];
    const MSGSINKVT *vt;
};
/* the message a sink receives: {1, the prize} in its first two words; the callers' frames give it 0x40 bytes */
struct SINKMSG {
    /* 0x0 */ s32 aw[2];
    u8 unknown_0x8[0x38];
};

struct OIDPLO {
    /* 0x0 */ s32 oid;
    /* 0x4 */ struct LO *plo;
};

/* ROWS3: rows3.h */

/* the HUD-spot ripple (a RIP of type 9, made by PripNewRipg; rip.h): a view of it as the two functions that start one see it, with
   the subclass's words past RIP's 0xF0 bytes. The RIP class keeps its vtable pointer at 0xEC (ConstructRipOfType stores it); slot 1 (entry at offset 8: delta, index, function) takes the position the
   ripple starts at, a scale and a flag. Read by hand: as a virtual the call loads the vtable pointer after the stores, retail before. */
struct RIPVTENTRY {
    s16 delta;
    s16 index;
    void (*fn)(void *, QW pos, float scale, int flags);
};
struct RIPVT {
    u8 unknown_0x0[0x8];
    /* 0x8 */ RIPVTENTRY slot1;
};
struct RIPHUDSPOT {
    u8 unknown_0x0[0x1C];
    /* 0x1C */ struct DPRIZE *pdprize;  /* SetDprizeCoinDprizes, SetDprizeCharmDprizes store the prize that spawned it */
    u8 unknown_0x20[0x20];
    /* 0x40 */ VECTOR rowObject[3];     /* the prize's world matrix, rows 0 to 2 (both functions copy PmatLoWorld's) */
    u8 unknown_0x70[0x7C];
    /* 0xEC */ const RIPVT *pvtrip;
    /* 0xF0 */ void **pparam;           /* the parameter block of the variant (D_002C0DA0 coin, D_002C0E10 charm): 28 words, its word 25 a function */
    /* 0xF4 */ struct DPRIZE *pdprizeTarget; /* the prize again */
    /* 0xF8 */ s32 field_0xF8;          /* both clear it */
};

struct DPRIZE : SO {
    virtual void SetDprizes(int dprizes); /* 76: SetDprizeCoinDprizes, SetDprizeCharmDprizes, SetDprizeKeyDprizes; CheckDprizeCollect passes 1,
                                             UpdateDprize 0, 2 and 4, PostDprizeLoad passes dprizesInitial */
    /* 0x150 */ s32 dprizes;             /* the state: UpdateDprize switches on it, RenderDprizeAll skips state 2 (hidden), InitDprize sets -1 */
    /* 0x154 */ f32 tDprizes;            /* the clock when the state last changed: UpdateDprize (state 4 times out against it) */
    /* 0x158 */ s32 dprizesInitial;      /* PostDprizeLoad passes it to SetDprizes (InitDprize clears it) */
    u8 unknown_0x15C[0xC];
    /* 0x168 */ struct SMA *psma;        /* the prize's animation: HandleDprizeMessage matches message 10's against it, RenderDprizeAll */
    /* 0x16C */ struct LO *ploShadow;    /* PostDprizeLoad: the class 0x12 object PloFindSwObjectByClass finds, removed at once (slot 9) */
    u8 unknown_0x170[0x10];
    /* 0x180 */ struct VECTOR velocity;  /* UpdateDprize: squared length against 10000 in state 0, z in states 3 and 4 */
    u8 unknown_0x190[0x10];
    /* 0x1A0 */ f32 field_0x1A0;         /* InitDprizeCoin 0.25, InitDprizeKey 0.75 */
    /* 0x1A4 */ struct OIDPLO aoidploGlint[3]; /* SetDprizeGlintOids stores the oids, PostDprizeLoad resolves each into plo */
    u8 unknown_0x1BC[0x8];
    /* 0x1C4 */ s32 landing;             /* UpdateDprize: state 4 clears it when the fall slows */
    /* 0x1C8 */ s32 collectable;         /* CheckDprizeCollect, FAbsorbDprizeWkr: 0 means it cannot be picked up (InitDprize sets 1) */
    /* 0x1CC */ f32 tExpire;             /* CheckDprizeCollect: the clock past which it is collected by itself */
    /* 0x1D0 */ f32 field_0x1D0;         /* InitDprizeCoin 250, InitDprizeKey 500 */
    /* 0x1D4 */ f32 field_0x1D4;         /* 150, 250 */
    /* 0x1D8 */ f32 field_0x1D8;         /* 45, 35 */
    /* 0x1DC */ f32 field_0x1DC;         /* 65, 35 */
    /* 0x1E0 */ f32 field_0x1E0;         /* 0.5, 0.6 */
    /* 0x1E4 */ f32 field_0x1E4;         /* 0.25, 0.6 */
    u8 unknown_0x1E8[0x1C];
    /* 0x204 */ struct OIDPLO aoidploB[3]; /* PostDprizeLoad resolves each oid into plo, as the glint triple; the objects found at [1] (0x210)
                                             and [2] (0x218) are the collect and expire sinks (MSGSINK): SetDprizeCoinDprizes tells the first
                                             {1, prize}, HandleDprizeMessage the second */
    u8 unknown_0x21C[0x14];
};

struct DPRIZECOIN : DPRIZE {
    /* 0x230 */ f32 waitMin; /* InitDprizeCoin sets 5; SetDprizeCoinDprizes draws the wait in state 0 */
    /* 0x234 */ f32 waitMax;
    /* 0x238 */ f32 wait;    /* UpdateDprizeCoin counts it down in state 0, then SetDprizes(5) */
};

struct DPRIZECHARM : DPRIZE {
    /* 0x230 */ f32 waitMin;
    /* 0x234 */ f32 waitMax;
    /* 0x238 */ f32 wait;
    /* 0x23C */ s32 healMin; /* SetDprizeCharmDprizes passes the range to the player's slot 81 */
    /* 0x240 */ s32 healMax;
};

struct DPRIZEKEY : DPRIZE {
    /* 0x230 */ void *ptask; /* SetDprizeKeyDprizes asks it for state 2 (RequestTaskState) */
};
#if defined(__mips__)
SLY2_OFFSET_CHECK(DPRIZE, dprizes, 0x150);
SLY2_OFFSET_CHECK(DPRIZE, psma, 0x168);
SLY2_OFFSET_CHECK(DPRIZE, velocity, 0x180);
SLY2_OFFSET_CHECK(DPRIZE, aoidploB, 0x204);
SLY2_SIZE_CHECK(DPRIZE, 0x230);
SLY2_OFFSET_CHECK(DPRIZECOIN, wait, 0x238);
SLY2_OFFSET_CHECK(DPRIZECHARM, healMax, 0x240);
SLY2_OFFSET_CHECK(DPRIZEKEY, ptask, 0x230);
SLY2_OFFSET_CHECK(RIPHUDSPOT, pdprize, 0x1C);
SLY2_OFFSET_CHECK(RIPHUDSPOT, rowObject, 0x40);
SLY2_OFFSET_CHECK(RIPHUDSPOT, pvtrip, 0xEC);
SLY2_OFFSET_CHECK(RIPHUDSPOT, pparam, 0xF0);
SLY2_OFFSET_CHECK(RIPHUDSPOT, field_0xF8, 0xF8);
#endif
#endif
