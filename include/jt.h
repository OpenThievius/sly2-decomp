/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JT, the player: class 52 of retail's class table, 0x1320 bytes, derived from STEP (include/step.h). It has no factory of its
   own: Sly (class 53, 0x2060 bytes, NewSly), Murray (54, 0x1B00) and Bentley (55, 0x1880) derive from it, and InitBentley
   calls InitJt, the init Sly's vtable keeps (slot 7). Its vtable adds slots 88 to 105. Sly 1 names the player JT (sly1
   include/jt.h, CC0), and so do the functions recovered from it.

   InitJt starts the player's parts in place (InitJmp at 0x2C0, InitAttach at 0x4C0, func_0019F3E8 at 0x9E0, InitJtZap at 0xDF0,
   the binoculars at 0xF00, InitJtPipe at 0xF50, func_00144638 at 0xFD0, CarryThrow_Init at 0x11B0); their fields are declared
   flat here, at their offsets in JT, until the parts get types of their own. A field is read or set by a JT method (its
   vtable slot is given), by a function that calls one of JT's own slots on the object (88 and up exist only in JT's
   family), by one whose other fields agree with those, or by two other readers that agree. C++ only. */
#ifndef SLY2_JT_H
#define SLY2_JT_H
#include "step.h"

struct STEPGUARD;
struct LOOT;
struct SM;
struct GADGETSTATE;
struct SEQNODE;
struct GADGETOBJ;

/* One of the player's three gadget slots: LoadJtGadgetSlots fills gadget from the level data, three 0xC-byte entries. */
struct GADGETSLOT {
    /* 0x0 */ s32 gadget;
    /* 0x4 */ void *ppool;      /* UseSlyGadget: PloLeaseCloneObject leases the gadget object from this pool (BENTLEYSLOT::ppool) */
    /* 0x8 */ struct LO *plo;   /* UseSlyGadget tests it and attaches to it; func_0018D698 subscribes to it */
};

struct JT : STEP {
    virtual void SetMode(int mode);     /* 88: SetBentleyMode (Bentley); func_0023C820 in Sly's vtable, as are 89 to 92, 94 and 103.
                                           JT_StartPose, StartAttach, FAbsorbHbskWkr pass one int */
    virtual int Slot89();               /* 89: JT_FPosing tests the result against 5 and 6 */
    virtual void Slot90();
    virtual void Slot91();
    virtual int Slot92(); /* 92: UpdateJtStand tests the result */
    virtual void Slot93();              /* 93: func_00140EB0; ZapContinue calls it without arguments */
    virtual void Slot94();
    virtual void SetFocus(int prioNear, struct STEPGUARD *pguardNear, int prioBest, struct STEPGUARD *pguardBest); /* 95: SetJtFocus; UpdateJtFocus */
    virtual void PredictLead(float dt, struct LEAD *plead); /* 96: PredictLoLead; GoalAnimLeap_SetState passes a 0x30-byte LEAD */
    virtual void Slot97(float *ppos);   /* 97: func_00141588; GetJtCpdefi passes a four-float output */
    virtual void Slot98();              /* 98: func_001409B8 */
    virtual int FCanUseGadget(int gadget); /* 99: func_00141C00, FBentleyCanUseGadget; UpdateLookRig */
    virtual void UseGadget(int gadget); /* 100: func_00141D38, UseBentleyGadget; SetJtGadgetSlotState */
    virtual void DrainGadget();         /* 101: DrainJtGadget */
    virtual void Slot102(int gadget);   /* 102: func_00141E28; SetJtGadgetSlotState when a gadget slot leaves state 1 */
    virtual const char *Slot103();      /* 103: LoadJtGadgetSlots reads the name it returns */
    virtual void Slot104();             /* 104: func_00141E30 */
    virtual void Slot105();             /* 105: func_00141E70, UpdateBentleyGadgetGlob */
    /* The parts InitJt starts in place, as the pointers the part's own functions take (their layouts are local to those files): the
       JMP at 0x2C0 (FJmpAllowsGadget), the attachment at 0x4C0 (FAttachAllowsGadget) and the pipe at 0xF50 (func_0019EEF0) */
    void *PvJmp() { return (char *)this + 0x2C0; }
    void *PvAttach() { return (char *)this + 0x4C0; }
    void *PvPipe() { return (char *)this + 0xF50; }
    void *PvPart9E0() { return (char *)this + 0x9E0; }   /* InitJt starts func_0019F3E8's part here */
    void *PvZap() { return (char *)this + 0xDF0; }       /* InitJtZap's part */
    void *PvBinoc() { return (char *)this + 0xF00; }     /* the binoculars */
    void *PvAttachCarry() { return (char *)this + 0x900; } /* in the attachment: func_001CD308 and func_001CC9A8 take it (its object is pcarried, 0x9A0) */
    void *PvVjoy() { return (char *)this + 0xFD0; }      /* the virtual joystick InitJt starts with func_00144638: UpdateJt passes it to
                                                           func_00144640 and func_001449C8, GoalFollowCrvVjoy steers it (func_001448F0) */
    void *PvCarry() { return (char *)this + 0x11B0; }    /* CarryThrow_Init's part */
    u8 unknown_0x2C0[0x4];
    /* 0x2C4 */ s32 field_0x2C4; /* in the JMP: SetMurrayMode (Murray slot 88) */
    u8 unknown_0x2C8[0x14];
    /* 0x2DC */ s32 jmpState; /* the jump state, in the JMP InitJt starts at 0x2C0: FInvulnerableJt (slot 76), func_00143C78 (85), func_00141588 (97) */
    u8 unknown_0x2E0[0xF8];
    /* 0x3D8 */ f32 field_0x3D8; /* InitBentley (Bentley slot 7) sets -70 */
    u8 unknown_0x3DC[0x58];
    /* 0x434 */ s32 field_0x434; /* GetJtCpdefi (JT slot 50) */
    u8 unknown_0x438[0x90];
    /* 0x4C8 */ s32 attachKind; /* in the attachment InitJt starts at 0x4C0: func_00143C78 (85); func_00211420, UpdateSndMix */
    /* 0x4CC */ s32 field_0x4CC; /* func_0018A428 (Sly slot 50) */
    u8 unknown_0x4D0[0x4];
    /* 0x4D4 */ struct ATTACHEDOBJ *field_0x4D4; /* in the attachment: AdjustSlyNewXp (Sly slot 55) tests its word at 0x1BC; the object's class is not recovered */
    u8 unknown_0x4D8[0x48];
    /* 0x520 */ void *field_0x520; /* BindJtStepAseg (Sly slot 90) */
    u8 unknown_0x524[0x47C];
    /* 0x9A0 */ struct SO *pcarried; /* in the attachment: func_00211420, after testing the object is class 52 */
    u8 unknown_0x9A4[0x18];
    /* 0x9BC */ s32 field_0x9BC; /* UseSlyGadget (Sly slot 100) */
    u8 unknown_0x9C0[0x4];
    /* 0x9C4 */ void *ptemplateTargetIndicator; /* UpdateSwTargetList spawns an indicator from it for a new candidate */
    u8 unknown_0x9C8[0x1C];
    /* 0x9E4 */ s32 field_0x9E4; /* in the part InitJt starts at 0x9E0: JT_TranslateToPos (STEP slot 29) clears it */
    u8 unknown_0x9E8[0x40C];
    /* 0xDF4 */ s32 zapState; /* in the zap state InitJt starts at 0xDF0: UpdateJt (16), func_00143C78 (85) */
    u8 unknown_0xDF8[0x4];
    /* 0xDFC */ s32 field_0xDFC; /* JT_FLethalHit (86) */
    /* 0xE00 */ s32 *pnHealth; /* SetJtHealth stores into it; bevy_player_p18_gadget_refill points it into the save variables; bevy_player_p18_gadget_144268 reads it (field_0xDFC is the maximum) */
    u8 unknown_0xE04[0xF8];
    /* 0xEFC */ void *pasegaHandle; /* UpdateJt (16) releases it once gone; RetractAsegaHandle and ReleaseAsegaHandle take its address */
    u8 unknown_0xF00[0x4];
    /* 0xF04 */ s32 binocState; /* the state of the binoculars InitJt starts at 0xF00 (PvBinoc, state at +4): StopBinoc switches on it, UpdateBinoc;
                                UpdateBentleyBinoc; func_0018D500 (Sly slot 106) and RenderJt test 1 (in use) */
    u8 unknown_0xF08[0x14];
    /* 0xF1C */ struct SO *field_0xF1C; /* func_001B81B8 (Murray slot 87) sets it to the held object */
    /* 0xF20 */ s32 binocPhase; /* in the binoculars InitJt starts at 0xF00: FInvulnerableJt (76); BindTextBinocReadout */
    u8 unknown_0xF24[0x14];
    /* 0xF38 */ struct GADGETLIST *pgadgetlist; /* func_00211148, func_002111F0: the list of gadgets whose names and string ids the menu shows */
    /* 0xF3C */ f32 field_0xF3C; /* BindTextBinocReadout, which reads binocPhase too */
    u8 unknown_0xF40[0x10];
    /* 0xF50 */ s32 field_0xF50; /* in the pipe state InitJt starts at 0xF50: func_00141588 (97); func_0018A428 */
    /* 0xF54 */ s32 field_0xF54; /* func_00141588 (97); func_0018A428 */
    u8 unknown_0xF58[0xA8];
    /* 0x1000 */ s32 field_0x1000; /* InitMurray sets 4, InitBentley 2 */
    u8 unknown_0x1004[0x1C];
    /* 0x1020 */ f32 field_0x1020; /* InitJt sets 100 */
    u8 unknown_0x1024[0x4];
    /* 0x1028 */ struct SM *psm; /* SetJtJtcs: IsmsFindSmOptional */
    u8 unknown_0x102C[0x4];
    /* 0x1030 */ void *field_0x1030; /* JT_StartPose (which calls slot 88, so holds a JT) */
    /* 0x1034 */ void *field_0x1034; /* JT_StartPose, UpdateJtStand */
    u8 unknown_0x1038[0x4];
    /* 0x103C */ f32 field_0x103C; /* InitJt sets 20 */
    /* 0x1040 */ s32 field_0x1040; /* InitBentley sets 0 */
    /* 0x1044 */ s32 fLook; /* func_001E5000: set while the seqnode's look target steers it (guess: reader is certain JT, class 0x34 test) */
    /* 0x1048 */ f32 field_0x1048; /* InitJt sets 125; func_00141588 */
    /* 0x104C */ f32 field_0x104C; /* func_00141588 */
    /* 0x1050 */ f32 field_0x1050; /* GetJtCpdefi (JT slot 50) */
    u8 unknown_0x1054[0xC];
    /* 0x1060 */ QW look; /* func_001E5000 */
    /* 0x1070 */ QW dir; /* func_001E5000 */
    /* 0x1080 */ f32 field_0x1080; /* GetMurrayCpdefi (Murray slot 50) */
    /* 0x1084 */ struct SEQNODE *pseqnode; /* UpdateJt (JT slot 16) passes it to UpdateSeqnodeVjoy when the goal stack is empty; bevy_player_p4_144068 tests it */
    /* 0x1088 */ struct GADGETSTATE *field_0x1088; /* SetMurrayLiftState (guess: one reader) */
    /* 0x108C */ s32 field_0x108C; /* SetBentleyState and func_00135EB0 (Bentley's slots) test it against 0 before blowing up a bomb or adding a safe point; func_001942F0 reads it too */
    u8 unknown_0x1090[0x8];
    /* 0x1098 */ f32 field_0x1098; /* InitMurray and InitBentley set -100 */
    /* 0x109C */ f32 field_0x109C; /* InitMurray and InitBentley set 100 */
    /* 0x10A0 */ f32 field_0x10A0; /* InitMurray and InitBentley set 50 */
    /* 0x10A4 */ f32 field_0x10A4; /* InitMurray and InitBentley set -10 */
    /* 0x10A8 */ f32 field_0x10A8; /* InitMurray and InitBentley set 250 */
    /* 0x10AC */ s32 field_0x10AC; /* InitMurray and InitBentley set 0 */
    /* 0x10B0 */ f32 field_0x10B0; /* InitMurray and InitBentley set 1 */
    /* 0x10B4 */ f32 field_0x10B4; /* InitMurray and InitBentley set 4500 */
    /* 0x10B8 */ void *field_0x10B8; /* PostBentleyLoad (Bentley slot 15) */
    u8 unknown_0x10BC[0xC];
    /* 0x10C8 */ s32 field_0x10C8; /* InitJt sets -1; UpdateSndMix */
    u8 unknown_0x10CC[0x8];
    /* 0x10D4 */ f32 field_0x10D4; /* InitJt sets 1 */
    /* 0x10D8 */ f32 field_0x10D8; /* InitJt sets 1 */
    /* 0x10DC */ sptr field_0x10DC; /* a STEPGUARD address: SetJtFocus (JT slot 95) stores pguardNear in it; bevy_player_input_from_pad_cm; func_001431D0 takes its goal stack */
    /* 0x10E0 */ s32 fFocusBusy; /* UpdateJtFocus (which calls slot 95, so holds a JT) */
    /* 0x10E4 */ s32 focusKind; /* InitJt sets -1; UpdateBinocHud */
    /* 0x10E8 */ struct STEPGUARD *pguardBest; /* SetJtFocus (JT slot 95) stores pguardBest in it */
    /* 0x10EC */ s32 focusMode; /* InitJt sets -1; UpdateBinocHud, UpdateSndMix */
    /* 0x10F0 */ s32 field_0x10F0; /* InitJt sets 1 */
    u8 unknown_0x10F4[0x4];
    /* 0x10F8 */ struct LO *ploLook; /* SetJtLookTarget sets it; func_001430C8 reads its world position (two readers) */
    /* 0x10FC */ s32 kindLook; /* SetJtLookTarget sets it; func_001430C8 switches on it */
    u8 unknown_0x1100[0x38];
    /* 0x1138 */ f32 field_0x1138; /* InitJt sets 1.5 */
    /* 0x113C */ f32 field_0x113C; /* InitJt sets 2.5 */
    /* 0x1140 */ f32 field_0x1140; /* InitJt sets 3 */
    /* 0x1144 */ f32 field_0x1144; /* InitJt sets 5 */
    /* 0x1148 */ s32 fGlance; /* func_00142868 sets it; ScheduleJtGlance picks the delay range by it; SetJtLookTarget sets it */
    /* 0x114C */ f32 tGlance; /* func_00142868 sets FLT_MAX; ScheduleJtGlance sets the next time; SetJtLookTarget tests for FLT_MAX */
    u8 unknown_0x1150[0x30];
    /* 0x1180 */ GADGETSLOT aslot[3]; /* LoadJtGadgetSlots (called by PostJtLoad, slot 15; calls slot 103) */
    u8 unknown_0x11A4[0x4];
    /* 0x11A8 */ struct LOOT *plootHeld; /* GiveJtLoot, DropJtLoot, DeliverJtLoot, Crfodb_OnGrab; level_loaded (class 52 objects) */
    u8 unknown_0x11AC[0x8];
    /* 0x11B4 */ s32 field_0x11B4; /* in the carry state InitJt starts at 0x11B0: UseSlyGadget (Sly slot 100) */
    u8 unknown_0x11B8[0x8];
    /* 0x11C0 */ struct GADGETOBJ *pgadgetLeased; /* in the carry state InitJt starts at 0x11B0: UseSlyGadget and UseBentleyGadget (slot 100 of
                                                    Sly and Bentley) store the gadget object they leased (gadgetobj.h) */
    u8 unknown_0x11C4[0x12C];
    /* 0x12F0 */ s32 fGadgetsAllowed; /* InitJt sets 1; FAttachAllowsGadget, FJmpAllowsGadget test it */
    /* 0x12F4 */ s32 field_0x12F4; /* JT_RetainSmKinds (slot 83) counts up, JT_ReleaseSmKinds (84) down */
    u8 unknown_0x12F8[0x4];
    /* 0x12FC */ s32 *pnPower; /* SetJtPower, which reads nPowerMax next to it */
    /* 0x1300 */ s32 nPowerMax; /* InitJt sets 100; SetJtPower */
    /* 0x1304 */ f32 field_0x1304; /* InitJt sets -60; SpendJtGadgetPower */
    /* 0x1308 */ f32 powerFraction; /* DrainJtPower accumulates the fraction of a power point; bevy_player_p18_gadget_refill clears it */
    /* 0x130C */ s32 field_0x130C; /* UseSlyGadget (Sly slot 100) */
    /* 0x1310 */ s32 field_0x1310; /* bevy_player_input_from_pad_cm */
    /* 0x1314 */ s32 field_0x1314; /* bevy_player_input_from_pad_cm */
    /* 0x1318 */ s32 sidDefault; /* InitJt sets -1; func_00211420 */
    u8 field_0x131C[0x4]; /* func_001B6BA8 passes its address */
};

#if defined(__mips__)
SLY2_SIZE_CHECK(GADGETSLOT, 0xC);
SLY2_OFFSET_CHECK(JT, field_0x434, 0x434);
SLY2_OFFSET_CHECK(JT, pnHealth, 0xE00);
SLY2_OFFSET_CHECK(JT, powerFraction, 0x1308);
SLY2_OFFSET_CHECK(JT, pgadgetLeased, 0x11C0);
SLY2_OFFSET_CHECK(JT, field_0x12F4, 0x12F4);
SLY2_OFFSET_CHECK(JT, field_0x9E4, 0x9E4);
SLY2_OFFSET_CHECK(JT, field_0x1050, 0x1050);
SLY2_OFFSET_CHECK(JT, pseqnode, 0x1084);
SLY2_OFFSET_CHECK(JT, field_0x108C, 0x108C);
SLY2_OFFSET_CHECK(JT, pguardBest, 0x10E8);
SLY2_OFFSET_CHECK(JT, ploLook, 0x10F8);
SLY2_OFFSET_CHECK(JT, kindLook, 0x10FC);
SLY2_OFFSET_CHECK(JT, fGlance, 0x1148);
SLY2_OFFSET_CHECK(JT, tGlance, 0x114C);
SLY2_SIZE_CHECK(JT, 0x1320);
SLY2_OFFSET_CHECK(JT, field_0x2C4, 0x2C4);
SLY2_OFFSET_CHECK(JT, jmpState, 0x2DC);
SLY2_OFFSET_CHECK(JT, field_0x3D8, 0x3D8);
SLY2_OFFSET_CHECK(JT, attachKind, 0x4C8);
SLY2_OFFSET_CHECK(JT, field_0x4CC, 0x4CC);
SLY2_OFFSET_CHECK(JT, field_0x520, 0x520);
SLY2_OFFSET_CHECK(JT, pcarried, 0x9A0);
SLY2_OFFSET_CHECK(JT, field_0x9BC, 0x9BC);
SLY2_OFFSET_CHECK(JT, ptemplateTargetIndicator, 0x9C4);
SLY2_OFFSET_CHECK(JT, zapState, 0xDF4);
SLY2_OFFSET_CHECK(JT, field_0xDFC, 0xDFC);
SLY2_OFFSET_CHECK(JT, pasegaHandle, 0xEFC);
SLY2_OFFSET_CHECK(JT, binocState, 0xF04);
SLY2_OFFSET_CHECK(JT, binocPhase, 0xF20);
SLY2_OFFSET_CHECK(JT, field_0xF3C, 0xF3C);
SLY2_OFFSET_CHECK(JT, field_0xF50, 0xF50);
SLY2_OFFSET_CHECK(JT, field_0xF54, 0xF54);
SLY2_OFFSET_CHECK(JT, field_0x1000, 0x1000);
SLY2_OFFSET_CHECK(JT, field_0x1020, 0x1020);
SLY2_OFFSET_CHECK(JT, field_0x1030, 0x1030);
SLY2_OFFSET_CHECK(JT, field_0x1034, 0x1034);
SLY2_OFFSET_CHECK(JT, field_0x103C, 0x103C);
SLY2_OFFSET_CHECK(JT, field_0x1040, 0x1040);
SLY2_OFFSET_CHECK(JT, field_0x1048, 0x1048);
SLY2_OFFSET_CHECK(JT, field_0x104C, 0x104C);
SLY2_OFFSET_CHECK(JT, field_0x1080, 0x1080);
SLY2_OFFSET_CHECK(JT, field_0x1088, 0x1088);
SLY2_OFFSET_CHECK(JT, field_0xF1C, 0xF1C);
SLY2_OFFSET_CHECK(JT, field_0x131C, 0x131C);
SLY2_OFFSET_CHECK(JT, field_0x1098, 0x1098);
SLY2_OFFSET_CHECK(JT, field_0x109C, 0x109C);
SLY2_OFFSET_CHECK(JT, field_0x10A0, 0x10A0);
SLY2_OFFSET_CHECK(JT, field_0x10A4, 0x10A4);
SLY2_OFFSET_CHECK(JT, field_0x10A8, 0x10A8);
SLY2_OFFSET_CHECK(JT, field_0x10AC, 0x10AC);
SLY2_OFFSET_CHECK(JT, field_0x10B0, 0x10B0);
SLY2_OFFSET_CHECK(JT, field_0x10B4, 0x10B4);
SLY2_OFFSET_CHECK(JT, field_0x10B8, 0x10B8);
SLY2_OFFSET_CHECK(JT, field_0x10C8, 0x10C8);
SLY2_OFFSET_CHECK(JT, field_0x10D4, 0x10D4);
SLY2_OFFSET_CHECK(JT, field_0x10D8, 0x10D8);
SLY2_OFFSET_CHECK(JT, fFocusBusy, 0x10E0);
SLY2_OFFSET_CHECK(JT, focusKind, 0x10E4);
SLY2_OFFSET_CHECK(JT, focusMode, 0x10EC);
SLY2_OFFSET_CHECK(JT, field_0x10F0, 0x10F0);
SLY2_OFFSET_CHECK(JT, field_0x1138, 0x1138);
SLY2_OFFSET_CHECK(JT, field_0x113C, 0x113C);
SLY2_OFFSET_CHECK(JT, field_0x1140, 0x1140);
SLY2_OFFSET_CHECK(JT, field_0x1144, 0x1144);
SLY2_OFFSET_CHECK(JT, aslot, 0x1180);
SLY2_OFFSET_CHECK(JT, plootHeld, 0x11A8);
SLY2_OFFSET_CHECK(JT, field_0x11B4, 0x11B4);
SLY2_OFFSET_CHECK(JT, fGadgetsAllowed, 0x12F0);
SLY2_OFFSET_CHECK(JT, pnPower, 0x12FC);
SLY2_OFFSET_CHECK(JT, nPowerMax, 0x1300);
SLY2_OFFSET_CHECK(JT, field_0x1304, 0x1304);
SLY2_OFFSET_CHECK(JT, field_0x130C, 0x130C);
SLY2_OFFSET_CHECK(JT, sidDefault, 0x1318);
SLY2_OFFSET_CHECK(JT, field_0x10DC, 0x10DC);
SLY2_OFFSET_CHECK(JT, field_0x1310, 0x1310);
SLY2_OFFSET_CHECK(JT, field_0x1314, 0x1314);
#endif
#endif
