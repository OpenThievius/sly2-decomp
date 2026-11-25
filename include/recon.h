/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RECON, a recon target of the binoculars (class 46 of retail's table, 0x120 bytes), and BINOCRECON, the binocular recon screen
   that lists the targets (kept at the player's 0x1D40). Proposed header (wave c5, folder W23): src/sprbuf-stepguard/ declares both
   per file. RECON is an XFM (xfm.h): InitRecon (func_00203568) calls InitXfm and LoadReconFromBrx (func_002035A8) calls
   LoadXfmFromBrx on it; its own fields start at 0xE0, where XFM ends. A field is here when two functions agree on it. C++ only. */
#ifndef SLY2_RECON_H
#define SLY2_RECON_H
#include "xfm.h"
#include "job.h"
#include "blot.h"

struct RECON : XFM {
    /* 0xE0 */ f32 radius;        /* LoadReconFromBrx sets 75.0 before loading; it fills radiusDefault from it when that stays 0 */
    /* 0xE4 */ f32 radiusDefault; /* LoadReconFromBrx */
    /* 0xE8 */ f32 radiusScale;   /* LoadReconFromBrx sets 0.25 */
    /* 0xEC */ TASK *ptask;       /* OnReconAdd (func_00203638), SetReconTargetDone, FReconTargetDone, bevy_ui_binoc_recon_202030 (reads its state): the task the recon belongs to */
    /* 0xF0 */ s32 fDone;         /* SetReconTargetDone stores it when there is no task, FReconTargetDone returns it */
    /* 0xF4 */ s32 field_0xF4;    /* InitRecon sets -1; LoadReconFromBrx (the default of idList); bevy_ui_binoc_recon_202768 copies it to the screen */
    /* 0xF8 */ s32 idList;        /* InitRecon sets -2; LoadReconFromBrx replaces -2 by field_0xF4; bevy_ui_binoc_recon_202030 skips a target at -1 */
    /* 0xFC */ s32 stream;        /* InitRecon sets -1; bevy_ui_binoc_recon_202768 (the stream of the binocular state 9) */
    /* 0x100 */ LO *plink;        /* ShowReconLinks, HideReconLinks, UpdateReconLinkFades, FReconTargetPickable (the linked object) */
    /* 0x104 */ f32 range;        /* LoadReconFromBrx sets 5000.0; UpdateReconLinkFades compares the distance with it */
    /* 0x108 */ s32 vis;          /* ClearReconVisibility clears it */
    u8 unknown_0x10C[0x4];
    /* 0x110 */ s32 field_0x110;  /* InitRecon sets -1 */
    u8 unknown_0x114[0xC];
};

struct BINOCRECON {
    /* 0x0 */ s32 state;
    u8 unknown_0x4[0x2C];
    /* 0x30 */ s32 ctarget;       /* the targets found: fun_00201dc8 stores CploFindSwObjectsByClass's count; ClearReconVisibility, ShowReconLinks, UpdateReconLinkFades, bevy_ui_binoc_recon_202030 walk them */
    /* 0x34 */ RECON *aptarget[16];
    /* 0x74 */ s32 clist;         /* the targets listed on the screen: bevy_ui_binoc_recon_202030 */
    /* 0x78 */ RECON *aptargetList[5];
    /* 0x8C */ RECON *precon;     /* the target being looked at (bevy_ui_binoc_recon_202768) */
    u8 unknown_0x90[0x10];
    /* 0xA0 */ s32 grfSaved;      /* bevy_ui_binoc_recon_202768 */
    /* 0xA4 */ void *pobjWipe;    /* fun_00201dc8 stores the object PloFindSwObject_thunk finds for 0x602 (bevy_ui_binoc_recon_202768 reads it as the wipe argument) */
    /* 0xA8 */ LO **pplo;         /* the focus object: fun_00201dc8 asks it whether it is class 0x35 */
    /* 0xAC */ BLOT *pblotA;      /* fun_00201dc8, bevy_ui_binoc_recon_202768 */
    /* 0xB0 */ BLOT *pblotB;
    u8 unknown_0xB4[0x4];
    /* 0xB8 */ s32 field_0xB8;    /* bevy_ui_binoc_recon_2022d8 */
    /* 0xBC */ s32 sidA;          /* func_00202730 looks the string up by it (PchzStringFromId) */
    /* 0xC0 */ s32 sidB;          /* func_002026F8 the same */
};
#endif
