/* SPDX-License-Identifier: GPL-3.0-or-later */
/* STEP, a walking object: class 51 of retail's class table, 0x2C0 bytes, derived from PO (include/po.h). Its vtable adds slots
   82 to 87 and holds InitStep (7), LoadStepFromBrx (14), UpdateStep (16), TranslateStepToPos (29), CloneStep (41),
   AdjustStepNewXp (55), PresetStepAccel (70). Named after those functions and Sly 1's STEP (sly1 include/step.h, CC0). Its fields
   are read by methods of JT (include/jt.h), which derives from it, or by two other readers. C++ only. */
#ifndef SLY2_STEP_H
#define SLY2_STEP_H
#include "po.h"

struct STEP : PO {
    virtual void Slot82();              /* 82: func_00205008, func_00140C30 (JT) */
    virtual void RetainSmKinds(int n1, int n2);       /* 83: RetainAloSmKinds, JT_RetainSmKinds */
    virtual void ReleaseSmKinds();      /* 84: ReleaseAloSmKinds, JT_ReleaseSmKinds */
    virtual void Slot85();              /* 85: func_002040F8, func_00143C78 (JT) */
    virtual int FLethalHit();           /* 86: func_00205D08, JT_FLethalHit */
    virtual void Slot87(int arg);       /* 87: func_00205D10; func_001B81B8 (Murray) calls it with a flag on the held object */
    u8 unknown_0x180[0x10];
    /* 0x190 */ QW velGoal; /* SetMurrayCarryState, func_001B5D30 (two readers) */
    u8 unknown_0x1A0[0x4];
    /* 0x1A4 */ s32 fLock; /* func_001750E0 */
    /* 0x1A8 */ f32 radHeading; /* ChooseJtSweepTarget, UpdateBinocHud (two readers) */
    u8 unknown_0x1AC[0x48];
    /* 0x1F4 */ f32 field_0x1F4; /* bevy_player_input_from_pad_cm */
    u8 unknown_0x1F8[0xC];
    /* 0x204 */ s32 field_0x204; /* func_00143C78 (JT slot 85) */
    /* 0x208 */ struct SO *psoSurface; /* what it stands on: func_00141588 (JT slot 97), UpdateJtStand */
    /* 0x20C */ f32 tJump; /* UpdateBentleyActive (from UpdateBentley, Bentley slot 16) */
    u8 unknown_0x210[0x8];
    /* 0x218 */ QW *ppos; /* the object's world position (a pointer to a quadword): AttachCrv_GetParam and Pipe_AddLoGrfEntry pass *ppos to the
                             curve search, GetJmpLaunchVelocity reads its z lane, the guard readers (UpdateGuard) copy it */
    u8 unknown_0x21C[0x4];
    /* 0x220 */ f32 field_0x220; /* InitMurray (Murray slot 7) sets 50 */
    u8 unknown_0x224[0x14];
    /* 0x238 */ f32 field_0x238; /* func_00141588 */
    u8 unknown_0x23C[0xC];
    /* 0x248 */ f32 field_0x248; /* func_00141588 */
    u8 unknown_0x24C[0x14];
    /* 0x260 */ f32 field_0x260; /* PostGuardLoad (GUARD slot 15) */
    /* 0x264 */ s32 keyHull; /* PostStepLoad: key of the hull geometry (-1 = none) */
    /* 0x268 */ void *pasegDefault; /* the fallback of SetMurrayAnimBase and func_00135D80 (slot 90 of Murray and Bentley); PostStepLoad stores the hull geometry PpartFindAlo returns here */
    u8 unknown_0x26C[0x4];
    /* 0x270 */ s32 field_0x270; /* UpdateJt (JT slot 16) */
    u8 unknown_0x274[0x20];
    /* 0x294 */ void *pcrv; /* func_0017C550, GoalGoto_SetState */
    u8 unknown_0x298[0x28];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(STEP, 0x2C0);
SLY2_OFFSET_CHECK(STEP, velGoal, 0x190);
SLY2_OFFSET_CHECK(STEP, radHeading, 0x1A8);
SLY2_OFFSET_CHECK(STEP, field_0x204, 0x204);
SLY2_OFFSET_CHECK(STEP, psoSurface, 0x208);
SLY2_OFFSET_CHECK(STEP, tJump, 0x20C);
SLY2_OFFSET_CHECK(STEP, field_0x220, 0x220);
SLY2_OFFSET_CHECK(STEP, ppos, 0x218);
SLY2_OFFSET_CHECK(STEP, field_0x238, 0x238);
SLY2_OFFSET_CHECK(STEP, field_0x248, 0x248);
SLY2_OFFSET_CHECK(STEP, field_0x260, 0x260);
SLY2_OFFSET_CHECK(STEP, pasegDefault, 0x268);
SLY2_OFFSET_CHECK(STEP, field_0x270, 0x270);
SLY2_OFFSET_CHECK(STEP, field_0x1F4, 0x1F4);
SLY2_OFFSET_CHECK(STEP, fLock, 0x1A4);
SLY2_OFFSET_CHECK(STEP, pcrv, 0x294);
#endif
#endif
