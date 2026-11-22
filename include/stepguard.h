/* SPDX-License-Identifier: GPL-3.0-or-later */
/* STEPGUARD, a guard: class 56 of retail's class table, 0x1010 bytes, derived from STEP (include/step.h). Like JT it has no vtable
   of its own in the table; its eleven subclasses (57 to 67, 0x1010 to 0x10A0 bytes) share its methods: HandleStepguardMessage (5),
   func_002064D8 (12), PostGuardLoad (15), UpdateGuard (16), RemoveStepguardHierarchy (22), AddStepguardHierarchy (23),
   OnGuardAdd (26), OnGuardRemove (27), CloneGuard (41), func_00206380 (61), FAbsorbGuardWkr (75), FIsGuardInvulnerable (76),
   NGuardAlertLevel (77), GrfGuardCustomXps (85), FIsGuardWkrLethal (86), func_001F1F38 (87), and two slots of its own (88, 89).
   Sly 1 names the class STEPGUARD (sly1 include/stepguard.h, CC0), and so do the names recovered from it. A field here is read or set by one of those methods (slot given) or by
   two other readers that agree, or by one function that is certainly guard code (it also reads named STEPGUARD fields of the same
   object, or gets the object from a guard method). C++ only. */
#ifndef SLY2_STEPGUARD_H
#define SLY2_STEPGUARD_H
#include "step.h"
#include "guard.h"

struct RIGOBJ;
struct ASEGA;
struct GOALSTACK;

/* two words read together by ExecuteGuardScriptCmd */
struct WORDPAIR { s32 first; s32 second; };

/* one queued guard action, 16 bytes: func_001F1900, func_001F1CF8 */
struct GUARDACT { s32 oid; s32 unk4; s32 nArg; s32 unkC; };

struct STEPGUARD : STEP {
    virtual void *Slot88();             /* 88: func_002082D0; GoalBrain_ChooseNextCommand uses its result */
    virtual void Slot89();              /* 89: func_00208BE0 */
    /* 0x2C0 */ u64 grfsgs; /* GrfGuardCustomXps (85); NGuardAlertLevel (77), func_001F1900 */
    u8 unknown_0x2C8[0x4];
    /* 0x2CC */ WORDPAIR field_0x2CC; /* ExecuteGuardScriptCmd */
    /* 0x2D4 */ WORDPAIR field_0x2D4; /* ExecuteGuardScriptCmd */
    /* 0x2DC */ u8 scratch[0xC]; /* func_0020A540 clears it (memset 0xC) */
    /* 0x2E8 */ s32 field_0x2E8; /* OnGuardRemove (27); func_0020A540 (the variant, compared and set) */
    /* 0x2EC */ struct LO *field_0x2EC; /* PostGuardLoad (15) */
    /* 0x2F0 */ struct HOME *phome; /* OnGuardAdd (26), PostGuardLoad (15) */
    u8 unknown_0x2F4[0xC];
    /* 0x300 */ QW posHome; /* OnGuardAdd (26) */
    /* 0x310 */ f32 radHome; /* OnGuardAdd (26) */
    u8 unknown_0x314[0x10];
    /* 0x324 */ u8 lm[0x8]; /* func_0017C3E8 passes its address to FCheckLm (an embedded LM; size to fDown, a guess); one reader */
    /* 0x32C */ s32 fDown; /* func_0017A8C8 */
    /* 0x330 */ s32 field_0x330; /* OnGuardRemove (27) */
    /* 0x334 */ s32 field_0x334; /* GoalHit_Activate (a guard goal: it also reads field_0x35C, heading and radHeading of this object) */
    /* 0x338 */ s32 field_0x338; /* OnGuardAdd (26); FIsGuardWkrLethal (86) */
    /* 0x33C */ s32 field_0x33C; /* OnGuardAdd (26); func_00155788 */
    /* 0x340 */ s32 field_0x340; /* OnGuardAdd (26) */
    /* 0x344 */ s32 field_0x344; /* OnGuardAdd (26) */
    u8 unknown_0x348[0x4];
    /* 0x34C */ struct ASEGA *pasega; /* func_002064D8 (slot 12) retracts it, UpdateGuard (16) releases it once FAsegaGone */
    u8 unknown_0x350[0xC];
    /* 0x35C */ s32 field_0x35C; /* func_0017A4E8, func_0017A558 pass its address to ReplaceSwHitFx */
    /* 0x360 */ f32 field_0x360; /* OnGuardRemove (27) */
    /* 0x364 */ s32 field_0x364; /* func_00208E70 (the sensing score function, certain guard code): gates holding and alert level 2 */
    /* 0x368 */ u8 field_0x368[0x8]; /* func_00208E70 passes its address to FCheckLm while the guard is in sgs 0x17 (an embedded LM) */
    /* 0x370 */ u8 field_0x370[0x8]; /* the same, otherwise */
    /* 0x378 */ f32 field_0x378; /* func_00208E70: alert level 2 range */
    /* 0x37C */ s32 field_0x37C; /* func_00208E70: gates alert level 1 */
    /* 0x380 */ u8 field_0x380[0x8]; /* func_00208E70 passes its address to FCheckLm for level 1 */
    /* 0x388 */ f32 field_0x388; /* func_00208E70: alert level 1 range */
    /* 0x38C */ struct BASIC *pbasicAlert; /* func_00208540 (the object its alert is made for), func_00208E70, GoalBrain_Update */
    /* 0x390 */ s32 field_0x390; /* OnGuardRemove (27) */
    /* 0x394 */ s32 cgroup; /* UpdateGuardSensor draft (nonmatching) */
    /* 0x398 */ s32 agroup[3]; /* UpdateGuardSensor draft */
    /* 0x3A4 */ s32 csensed; /* UpdateGuardSensor draft */
    /* 0x3A8 */ s32 cignoredClass; /* ClearGuardIgnoredClasses */
    u8 unknown_0x3AC[0x3C0 - 0x3AC];
    /* 0x3C0 */ s32 cclassFilter; /* ClearGuardClassFilters */
    u8 unknown_0x3C4[0x3CC - 0x3C4];
    /* 0x3CC */ struct ALERT *palert; /* func_00208540: PalertEnsure's result (the UpdateGuardSensor draft called it ptarget) */
    /* 0x3D0 */ s32 blocked; /* func_0020A298 */
    u8 unknown_0x3D4[0x3F4 - 0x3D4];
    /* 0x3F4 */ struct LO *field_0x3F4; /* PostGuardLoad (15); func_001F17F8 */
    /* 0x3F8 */ struct LO *field_0x3F8; /* PostGuardLoad (15); func_001F17F8 */
    /* 0x3FC */ s32 state; /* func_001F17F8 */
    /* 0x400 */ f32 tState; /* func_001F17F8 */
    /* 0x404 */ GUARDACT aguardact[8]; /* func_001F1900, func_001F1CF8, func_001F1EB8 */
    /* 0x484 */ s32 cguardact; /* func_001F1900 and func_001F1CF8 (two readers) */
    /* 0x488 */ s32 iguardactCur; /* func_001F1CF8, func_001F1EB8 */
    /* 0x48C */ s32 fActionDone; /* func_001F1CF8 */
    u8 unknown_0x490[0x4];
    /* 0x494 */ struct RIGOBJ *prig; /* OnGuardAdd (26); func_001F1900, func_001F1CF8, func_001F17F8 */
    /* 0x498 */ struct FALLCHECK *pfallcheck; /* PostGuardLoad (15), OnGuardAdd (26); UpdateGuard (16) passes it to UpdateFallCheck */
    /* 0x49C */ struct GUARDDAMAGE *pdamage; /* PostGuardLoad (15), OnGuardAdd (26), HandleStepguardMessage (5), UpdateGuard (16) */
    u8 unknown_0x4A0[0x4];
    /* 0x4A4 */ s32 field_0x4A4; /* func_0014B1A0 */
    u8 unknown_0x4A8[0x8];
    /* 0x4B0 */ QW posCopy; /* UpdateGuard (16): a copy of *ppos; GoalBrain_SetCommand (command 19) hands it to the snap goal */
    /* 0x4C0 */ s32 canim; /* PguardanimBestMatch: entries in the table at 0x4D0 */
    u8 unknown_0x4C4[0xC];
    /* 0x4D0 */ GUARDANIM aanim[0x20]; /* PguardanimBestMatch, BindGuardAnimrefs, CloneGuardAnimrefs: 0x400 bytes up to the arrays */
    /* 0x8D0 */ ANIMREF aarefA[26]; /* BindGuardAnimrefs, CloneGuardAnimrefs (two readers agree) */
    /* 0xA70 */ ANIMREF aarefB[26]; /* the same; func_001796D0 points a GoalHit at one of them */
    /* 0xC10 */ ANIMREF aarefC[26]; /* the same */
    u8 unknown_0xDB0[0xB4];
    /* 0xE64 */ s32 sensing; /* func_00208D70 */
    /* 0xE68 */ s32 field_0xE68; /* func_00208BE0 (89) */
    /* 0xE6C */ f32 field_0xE6C; /* func_00172560 (GoalSearch; it also reads field_0xE78 of the same guard): GRandInRange's minimum */
    /* 0xE70 */ f32 field_0xE70; /* the same: its maximum */
    u8 unknown_0xE74[0x4];
    /* 0xE78 */ s32 field_0xE78; /* OnGuardAdd (26) */
    u8 unknown_0xE7C[0x8];
    /* 0xE84 */ s32 field_0xE84; /* OnGuardAdd (26) */
    /* 0xE88 */ s32 field_0xE88; /* OnGuardAdd (26) */
    u8 unknown_0xE8C[0x2C];
    /* 0xEB8 */ s32 aoid[8]; /* ResolveGuardAimObjects: object ids to look up */
    /* 0xED8 */ s32 caoid; /* ResolveGuardAimObjects: entries in aoid */
    /* 0xEDC */ s32 afound[8]; /* ResolveGuardAimObjects: the objects found */
    /* 0xEFC */ s32 cfound; /* ResolveGuardAimObjects: entries in afound */
    /* 0xF00 */ struct AIMSTATE *paimstate; /* UpdateGuard (16): while it is set, UpdateGuard waits for its animref to finish */
    /* 0xF04 */ f32 tCooldown; /* a clock time: GoalHit_Activate clears it; func_00175FF0 and GoalNotice_SetState compare the clock with it
                                (lwc1), func_00155AE0 sets it to the clock plus a random wait or to FLT_MAX */
    /* 0xF08 */ struct XF *paim; /* func_0020AC28: the aim transform */
    /* 0xF0C */ void *pact; /* func_0020AC28: what func_0012DC18 returned for it; func_0012E460 gets its address */
    /* 0xF10 */ s32 field_0xF10; /* func_0020AC28: its third argument */
    u8 unknown_0xF14[0xC];
    /* 0xF20 */ QW vecLook; /* func_0020AC28: its fourth argument */
    u8 unknown_0xF30[0xC];
    /* 0xF3C */ s32 fFlag; /* func_001752F0 */
    u8 unknown_0xF40[0x20];
    /* 0xF60 */ s32 field_0xF60; /* func_0017B750 */
    /* 0xF64 */ struct SENSOR *psensor; /* OnGuardAdd (26), func_00208BE0 (89), CloneGuard (41) */
    /* 0xF68 */ struct LO *ptargetGoto; /* SetGuardGotoTarget; GoalBrain_SetCommand (command 16) hands it to the goto-target goal, which reads its position */
    u8 unknown_0xF6C[0x4];
    /* 0xF70 */ QW posGoto; /* SetGuardGotoTarget; GoalBrain_SetCommand (command 16) */
    /* 0xF80 */ s32 modePath; /* ClearGuardPathMode, SetGuardPathTarget; func_00209C88 switches on it (0 to 3) */
    /* 0xF84 */ void *ptargetPath; /* ClearGuardPathMode, SetGuardPathTarget; func_00209C88 (the slot-82 call's object) */
    /* 0xF88 */ f32 sPath; /* SetGuardPathTarget (FindCrvClosestPointAll out), func_00209C88 */
    /* 0xF8C */ s32 nPath; /* SetGuardPathTarget */
    /* 0xF90 */ void *prefPath; /* SetGuardPathTarget; func_00209C88 (its PosLoWorld) */
    u8 unknown_0xF94[0x28];
    /* 0xFBC */ s32 mode; /* SetGuardMode, GoalBrain_ChooseNextCommand, SetSwGuardsFrozen */
    /* 0xFC0 */ f32 tMode; /* SetGuardMode */
    /* 0xFC4 */ void *field_0xFC4; /* PostGuardLoad (15) */
    /* 0xFC8 */ s32 field_0xFC8; /* func_00209098 (GoalIdle_Update passes the guard) */
    u8 unknown_0xFCC[0x4];
    /* 0xFD0 */ GUARDHEADING heading; /* GrfGuardCustomXps (85) reads its first word; OnGuardAdd, CloneGuard and UpdateGuard pass its address */
    /* 0xFE0 */ struct STEPGUARD *pnext; /* the world list of guards: UpdateJtFocus */
    u8 unknown_0xFE4[0x4];
    /* 0xFE8 */ u32 grf; /* OnGuardAdd (26); func_0017D450, func_0017D6C8 */
    /* 0xFEC */ struct LO *field_0xFEC; /* OnGuardAdd (26) */
    u8 unknown_0xFF0[0x8];
    /* 0xFF8 */ f32 field_0xFF8; /* AddStepguardHierarchy (23), RemoveStepguardHierarchy (22) */
    /* 0xFFC */ s32 busyGoalCount; /* AddGuardBusyGoal, RemoveGuardBusyGoal */
    /* 0x1000 */ s32 field_0x1000; /* func_0020B590 */
    u8 unknown_0x1004[0xC];

    /* the goal stack: STEP::pgoalstack() (step.h) */
};

#if defined(__mips__)
SLY2_SIZE_CHECK(STEPGUARD, 0x1010);
SLY2_OFFSET_CHECK(STEPGUARD, grfsgs, 0x2C0);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x2E8, 0x2E8);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x2EC, 0x2EC);
SLY2_OFFSET_CHECK(STEPGUARD, phome, 0x2F0);
SLY2_OFFSET_CHECK(STEPGUARD, posHome, 0x300);
SLY2_OFFSET_CHECK(STEPGUARD, radHome, 0x310);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x330, 0x330);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x338, 0x338);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x33C, 0x33C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x340, 0x340);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x35C, 0x35C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x344, 0x344);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x360, 0x360);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x390, 0x390);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x3F4, 0x3F4);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x3F8, 0x3F8);
SLY2_OFFSET_CHECK(STEPGUARD, cguardact, 0x484);
SLY2_OFFSET_CHECK(STEPGUARD, prig, 0x494);
SLY2_OFFSET_CHECK(STEPGUARD, pfallcheck, 0x498);
SLY2_OFFSET_CHECK(STEPGUARD, pdamage, 0x49C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xE68, 0xE68);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xE78, 0xE78);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xE84, 0xE84);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xE88, 0xE88);
SLY2_OFFSET_CHECK(STEPGUARD, psensor, 0xF64);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xFC4, 0xFC4);
SLY2_OFFSET_CHECK(STEPGUARD, heading, 0xFD0);
SLY2_OFFSET_CHECK(STEPGUARD, grf, 0xFE8);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xFEC, 0xFEC);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xFF8, 0xFF8);
SLY2_OFFSET_CHECK(STEPGUARD, fDown, 0x32C);
SLY2_OFFSET_CHECK(STEPGUARD, blocked, 0x3D0);
SLY2_OFFSET_CHECK(STEPGUARD, state, 0x3FC);
SLY2_OFFSET_CHECK(STEPGUARD, tState, 0x400);
SLY2_OFFSET_CHECK(STEPGUARD, aguardact, 0x404);
SLY2_OFFSET_CHECK(STEPGUARD, iguardactCur, 0x488);
SLY2_OFFSET_CHECK(STEPGUARD, fActionDone, 0x48C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x2CC, 0x2CC);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x2D4, 0x2D4);
SLY2_OFFSET_CHECK(STEPGUARD, scratch, 0x2DC);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x4A4, 0x4A4);
SLY2_OFFSET_CHECK(STEPGUARD, canim, 0x4C0);
SLY2_OFFSET_CHECK(STEPGUARD, aanim, 0x4D0);
SLY2_OFFSET_CHECK(STEPGUARD, sensing, 0xE64);
SLY2_OFFSET_CHECK(STEPGUARD, aoid, 0xEB8);
SLY2_OFFSET_CHECK(STEPGUARD, caoid, 0xED8);
SLY2_OFFSET_CHECK(STEPGUARD, afound, 0xEDC);
SLY2_OFFSET_CHECK(STEPGUARD, cfound, 0xEFC);
SLY2_OFFSET_CHECK(STEPGUARD, paim, 0xF08);
SLY2_OFFSET_CHECK(STEPGUARD, pact, 0xF0C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xF10, 0xF10);
SLY2_OFFSET_CHECK(STEPGUARD, vecLook, 0xF20);
SLY2_OFFSET_CHECK(STEPGUARD, fFlag, 0xF3C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xF60, 0xF60);
SLY2_OFFSET_CHECK(STEPGUARD, modePath, 0xF80);
SLY2_OFFSET_CHECK(STEPGUARD, ptargetPath, 0xF84);
SLY2_OFFSET_CHECK(STEPGUARD, sPath, 0xF88);
SLY2_OFFSET_CHECK(STEPGUARD, nPath, 0xF8C);
SLY2_OFFSET_CHECK(STEPGUARD, prefPath, 0xF90);
SLY2_OFFSET_CHECK(STEPGUARD, mode, 0xFBC);
SLY2_OFFSET_CHECK(STEPGUARD, tMode, 0xFC0);
SLY2_OFFSET_CHECK(STEPGUARD, pnext, 0xFE0);
SLY2_OFFSET_CHECK(STEPGUARD, busyGoalCount, 0xFFC);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x1000, 0x1000);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x334, 0x334);
SLY2_OFFSET_CHECK(STEPGUARD, pasega, 0x34C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x364, 0x364);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x368, 0x368);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x370, 0x370);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x378, 0x378);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x37C, 0x37C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x380, 0x380);
SLY2_OFFSET_CHECK(STEPGUARD, field_0x388, 0x388);
SLY2_OFFSET_CHECK(STEPGUARD, pbasicAlert, 0x38C);
SLY2_OFFSET_CHECK(STEPGUARD, cignoredClass, 0x3A8);
SLY2_OFFSET_CHECK(STEPGUARD, cclassFilter, 0x3C0);
SLY2_OFFSET_CHECK(STEPGUARD, palert, 0x3CC);
SLY2_OFFSET_CHECK(STEPGUARD, posCopy, 0x4B0);
SLY2_OFFSET_CHECK(STEPGUARD, aarefA, 0x8D0);
SLY2_OFFSET_CHECK(STEPGUARD, aarefB, 0xA70);
SLY2_OFFSET_CHECK(STEPGUARD, aarefC, 0xC10);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xE6C, 0xE6C);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xE70, 0xE70);
SLY2_OFFSET_CHECK(STEPGUARD, paimstate, 0xF00);
SLY2_OFFSET_CHECK(STEPGUARD, tCooldown, 0xF04);
SLY2_OFFSET_CHECK(STEPGUARD, ptargetGoto, 0xF68);
SLY2_OFFSET_CHECK(STEPGUARD, posGoto, 0xF70);
SLY2_OFFSET_CHECK(STEPGUARD, field_0xFC8, 0xFC8);
#endif
#endif
