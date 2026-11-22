/* SPDX-License-Identifier: GPL-3.0-or-later */
/* COIN: the coin and cluebottle prize class of src/new_1c76d0 (SetCoinState, UpdateCoin, LoadCoinFromBrx, SelectCoinLootDef,
   func_001C7988 to func_001C7A10). A DPRIZE (include/dprize.h) with the DPRIZECOIN fields and a table of loot definitions at 0x23C to 0x244. C++ gets
   the class, C a view with the same offsets. Names are ours, from what those methods do. */
#ifndef SLY2_COIN_H
#define SLY2_COIN_H
#include "types.h"

/* one 0x2C-byte entry of COIN::aloot: func_001C7988 fills id, lootkc, cmesh and the two -1 words, func_001C7A10 appends a mesh to
   ameshShown, SelectCoinLootDef reads id, cmesh and ameshShown, SetCoinState formats lootkc into a name */
struct COINLOOTDEF {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 lootkc;
    u8 unknown_0x8[0xC];
    /* 0x14 */ s32 field_0x14; /* func_001C7988 sets -1 */
    /* 0x18 */ s32 field_0x18; /* func_001C7988 sets -1 */
    /* 0x1C */ s32 cmesh;      /* the count of ameshShown: func_001C7988 clears it, func_001C7A10 (below 3) and SelectCoinLootDef */
    /* 0x20 */ s32 ameshShown[3];
};

#ifdef __cplusplus
#include "dprize.h"
/* not a DPRIZECOIN subclass: that class's size rounds up to 0x240 (16-byte alignment), so its fields are repeated here */
struct COIN : DPRIZE {
    /* 0x230 */ f32 waitMin;         /* DPRIZECOIN: InitDprizeCoin sets 5; SetCoinState draws the wait in state 0 */
    /* 0x234 */ f32 waitMax;
    /* 0x238 */ f32 wait;            /* UpdateCoin counts it down in state 0, then SetDprizes(5) */
    /* 0x23C */ s32 cloot;           /* func_001C7988 (appends while below 0x20), SelectCoinLootDef */
    /* 0x240 */ COINLOOTDEF *aloot;  /* the same two */
    /* 0x244 */ COINLOOTDEF *cur;    /* the selected entry: func_001C7A08 clears it, func_001C7A10, SetCoinState, SelectCoinLootDef */
};
#if defined(__mips__)
SLY2_OFFSET_CHECK(COIN, cloot, 0x23C);
SLY2_OFFSET_CHECK(COIN, cur, 0x244);
#endif
#else
struct COIN {
    u8 unknown_0x0[0x23C];
    s32 cloot;
    struct COINLOOTDEF *aloot;
    struct COINLOOTDEF *cur;
};
#endif
#endif
