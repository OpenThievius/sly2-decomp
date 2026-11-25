/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JTZAP, the part InitJt starts at JT + 0xDF0 (JT::PvZap, include/jt.h), and ZAPXP, the contact record its AdjustJtZapNewXp
   writes. Private to the ub-light module: layouts of what the module's functions read, nothing more. C++ only. */
#ifndef SLY2_JTZAP_H
#define SLY2_JTZAP_H
#include "jt.h"
#include "so.h"
#include "bytes8.h"

struct JTZAP {
    /* 0x00 */ JT *pjt;          /* func_001A1FA8, func_001A2080: SetJmpState gets pjt->PvJmp(); WarpZapToSafePoint passes it on */
    /* 0x04 */ s32 state;        /* AdjustJtZapNewXp (switch), func_001A2160 (switch), func_001A23C0 (-1 test) */
    /* 0x08 */ f32 tState;       /* UpdateZapPost: time of the last state change (state 7 waits 0.25 s, FJtStuck takes it); certain, zap part's own function */
    /* 0x0C */ s32 field_0xC;   /* InitJtZap sets 0x28 (the zap part's own initialiser) */
    /* 0x10 */ s32 *phealth;     /* func_001A1FA8, func_001A2080 test it > 0; func_001A23C0 tests it <= 0 (guess: reader is the zap part, certain) */
    u8 unknown_0x14[0x8];
    /* 0x1C */ BYTES8 continuation;  /* SetZapContinuation stores the 8 bytes (an unaligned member-function pointer), ZapContinue takes and clears it; certain */
    u8 unknown_0x24[0xC];
    /* 0x30 */ SO *ptarget;      /* func_001A1FA8, func_001A2080: tests its grfso bit 33 */
    u8 unknown_0x34[0x5C];
    /* 0x90 */ s32 flash;        /* func_001A23C0 compares it with 1; UpdateZapPost tests it against -1 (no flash) */
    /* 0x94 */ f32 tPulseStart;  /* UpdateZapPost: the pulse's phase starts here */
    /* 0x98 */ f32 tFlash;       /* UpdateZapPost: start of the fade-out */
    /* 0x9C */ f32 dtFlash;      /* UpdateZapPost: its length */
};

struct ZAPXP {
    /* 0x00 */ u32 grf;          /* func_001A2160 sets bit 0 */
    u8 unknown_0x4[0x30];
    /* 0x34 */ s32 field_0x34;   /* func_001A2160 clears it by state */
    u8 unknown_0x38[0x5C];
    /* 0x94 */ float field_0x94; /* AdjustJtZapNewXp */
    /* 0x98 */ float field_0x98; /* AdjustJtZapNewXp (cleared in states 4 and 12) */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(JTZAP, state, 0x4);
SLY2_OFFSET_CHECK(JTZAP, phealth, 0x10);
SLY2_OFFSET_CHECK(JTZAP, ptarget, 0x30);
SLY2_OFFSET_CHECK(JTZAP, tState, 0x8);
SLY2_OFFSET_CHECK(JTZAP, continuation, 0x1C);
SLY2_OFFSET_CHECK(JTZAP, flash, 0x90);
SLY2_OFFSET_CHECK(JTZAP, dtFlash, 0x9C);
SLY2_OFFSET_CHECK(ZAPXP, field_0x94, 0x94);
SLY2_OFFSET_CHECK(ZAPXP, field_0x98, 0x98);
#endif
#endif
