/* SPDX-License-Identifier: GPL-3.0-or-later */
/* KEYPAD: the PO subclass of src/new_1c76d0 (PostKeypadLoad func_001C82F0 at slot 15, func_001C8730 the state switch, func_001C8280
   its init, func_001C8350 its update). Its size is not known; the fields start at PO's 0x180. Names are ours, from what those
   functions do. C++ gets the class, C a view with the same offsets. */
#ifndef SLY2_KEYPAD_H
#define SLY2_KEYPAD_H
#include "types.h"
#include "xf.h"

#ifdef __cplusplus
#include "po.h"
struct KEYPAD : PO {
    /* 0x180 */ s32 state;        /* func_001C8730 (-1 to 5); func_001C8350 */
    /* 0x184 */ f32 tState;       /* func_001C8730: the clock when the state last changed */
    /* 0x188 */ s32 stateCell;   /* func_001C8918 (the cell/camera state setter func_001C8730 calls): -1 to 2; one reader */
    /* 0x18C */ f32 tStateCell;  /* func_001C8918: the clock when stateCell last changed */
    /* 0x190 */ PO *ppoUser;      /* func_001C8730: the object using it (a PO); func_001C8730 calls its SetPlayable(1) and clears it in states 0 and 5 */
    /* 0x194 */ s32 cnt;          /* func_001C8730 sets 5 in state 2 */
    /* 0x198 */ s32 target;      /* func_001C8350 (the keypad's update) compares it with field_0x1F0 (the code) in state 2 */
    /* 0x19C */ s32 jsg;          /* func_001C8730 starts and stops it; func_001C8350 */
    /* 0x1A0 */ void *hAsega;    /* func_001C8918: the asega handle it releases and ApplyAsegToHandle fills (one reader) */
    /* 0x1A4 */ s32 stream;       /* func_001C8730: the playing stream, stopped on every state change */
    /* 0x1A8 */ void *acell[8];  /* func_001C8918: the objects the player is attached to, indexed by cnt (one reader) */
    u8 unknown_0x1C8[0x4];
    /* 0x1CC */ void *aaseg[8];  /* func_001C8918: the animation played for the cell cnt (one reader) */
    u8 unknown_0x1EC[0x4];
    /* 0x1F0 */ s32 field_0x1F0;  /* func_001C8280 sets 0x7B; func_001C8350 */
    /* 0x1F4 */ s32 streamB;      /* func_001C8730 starts it in state 2 */
    /* 0x1F8 */ s32 streamClue;  /* func_001C8280 sets -1 like streamA and B; func_001C8AF0 starts it when set */
    /* 0x1FC */ s32 streamA;      /* func_001C8730 starts it when leaving state 3 */
    /* 0x200 */ s32 gadget;       /* func_001C8730 marks it acquired in state 3 */
    /* 0x204 */ XF *pxf;          /* func_001C82F0 stores func_001F4C58's result */
    /* 0x208 */ void *pcamera;   /* func_001C8918 (stateCell 1): what the player is attached to while the camera moves (one reader) */
    /* 0x20C */ s32 ajsg[8];      /* func_001C8730 indexes it by state */
};
#if defined(__mips__)
SLY2_OFFSET_CHECK(KEYPAD, state, 0x180);
SLY2_OFFSET_CHECK(KEYPAD, ppoUser, 0x190);
SLY2_OFFSET_CHECK(KEYPAD, jsg, 0x19C);
SLY2_OFFSET_CHECK(KEYPAD, stream, 0x1A4);
SLY2_OFFSET_CHECK(KEYPAD, streamB, 0x1F4);
SLY2_OFFSET_CHECK(KEYPAD, pxf, 0x204);
SLY2_OFFSET_CHECK(KEYPAD, ajsg, 0x20C);
#endif
#else
struct KEYPAD {
    u8 unknown_0x0[0x204];
    struct XF *pxf;
};
#endif
#endif
