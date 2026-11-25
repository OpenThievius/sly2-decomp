/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SW, the world: class 1 of retail's class table (0x2BAAE8, config/recovered/class_diff.tsv), 0x4790 bytes, derived from the
   root class (include/lo.h BASIC). The game keeps one, a static global at 0x3DD490 (B_003DD490), and passes its address to the
   *Sw* functions. Sly 1's SW derives from LO; Sly 2's does not, and its layout is its own: every field below comes from Sly 2's
   matched code (docs/ROADMAP.md "Next", item 1).

   A field is here when a matched function reads it at that offset through the global or a *Sw* function's argument (the
   class is then certain, so one reader is enough) and no matched function reads the offset as another type; the readers are
   listed. The save paths are named after the strings retail passes to PsavepathNew for each (CreateSwSavePaths). C++ only. */
#ifndef SLY2_SW_H
#define SLY2_SW_H
#include "lo.h"
#include "dl.h"
#include "sl.h"
#include "dcb.h"

struct BLOCK;
struct TIMEDCALL;
struct JOB;
struct TASK;
struct WARP;
struct OBR;
struct PO;
struct CLONESET;
struct PRIPG;
struct BSPNODE;
struct TARGET;
struct SAVEPATH;
struct CB;
struct SWNODE;
struct PZGRAPH;
struct SWSTRING;
struct JOY;
struct LIGHT;

/* a 0x28-byte entry of the world's table at 0x45E8: AllocSwBuffers passes each to func_001BE398 with an initialised ZPR */
struct ZPRENTRY {
    u8 unknown_0x0[0x28];
};

/* A level's identity block, 0x40 bytes: a load request carries one at 4, the world keeps the current one at 0x3C40. Two blocks
   name the same level when their words 0x8 and 0x38, xored together, agree (ActivateWipe, RequestTransition). */
struct LEVELID {
    u8 unknown_0x0[0x8];
    /* 0x08 */ u32 field_0x8;
    u8 unknown_0xC[0x2C];
    /* 0x38 */ u32 field_0x38;
    u8 unknown_0x3C[0x4];
};

/* A level load request (SetSwLoadRequest copies one, 0x4C bytes, into the world). func_00165280 and func_0020E180 test and set
   bits 4 and 8 of its first word; func_00165280 also writes 0x44 and 0x48. */
struct LOADREQ {
    /* 0x00 */ s32 grf;      /* signed: func_00165280 clears bit 8 with an addiu of -9 */
    /* 0x04 */ struct LEVELID level; /* ActivateWipe compares it with the world's (SW::level) */
    /* 0x44 */ s32 field_0x44;
    /* 0x48 */ s32 field_0x48;
};

/* An entry of the world's table at 0x3F14: flags and an object (AddSwGrfEntry adds one; SolveSw and func_001CDA80 walk them and
   call LO slots 17 and 19 on the object). */
struct GRFENTRY {
    u32 grf;
    struct LO *plo;
};

/* A slot heap: a pool of same-sized slots (Sly 1's name, sly1 include/slotheap.h, CC0). Sly 2's is 0x18 bytes: the world keeps
   pairs of them back to back (slotheapRipg 0x403C and slotheapRip 0x4054, PripgNew and PripNewRipg), and a field follows
   each one 0x18 bytes on (pcbFirst after the callbacks' heap at 0x3C90, dlWkr after slotheapWkr). PblipgNew reads two fields
   of the blip groups' heap before it allocates: no free slot and a fixed size means no new group. */
struct SLOTHEAP {
    /* 0x00 */ s32 cb;                /* PvAllocSlotheapImpl: slot size */
    /* 0x04 */ s32 c;                 /* PvAllocSlotheapImpl: slots per block */
    /* 0x08 */ s32 cbAlign;           /* PvAllocSlotheapImpl */
    /* 0x0C */ void *pslotFree;       /* PblipgNew, PvAllocSlotheapImpl, FreeSlotheapPv */
    /* 0x10 */ s32 cslotUsed;         /* PvAllocSlotheapImpl (++), FreeSlotheapPv (--) */
    /* 0x14 */ void *pblockCur;       /* PvAllocSlotheapImpl stores the block it allocates; PblipgNew tests it for nonzero */
};

/* The target interface a candidate of the player's target list points at: its label id at 0x14 and its vtable at 0x20
   (UpdateSwTargetList). */
struct TGTDEF {
    u8 unknown_0x0[0x14];
    /* 0x14 */ s32 idLabel;
    u8 unknown_0x18[0x8];
    /* 0x20: the vtable pointer */
    virtual int FGetWrapRange(float *prange);   /* 1: two floats, the low and the high end */
    virtual void Slot2();
    virtual void GetIndicatorPos(struct JT *pjt, QW *ppos, int grf, float s); /* 3 */
};

/* A candidate of the player's target list, 0x30 bytes: the world keeps four (atgt, from 0x4680) and UpdateSwTargetList merges
   the player's new ones into them. s and dsdt are the smoothed position along the target and its rate. */
struct TGT {
    /* 0x00 */ s32 oid;
    /* 0x04 */ TGTDEF *ptgtdef;
    /* 0x08 */ f32 sRank;
    /* 0x0C */ s32 iRank;
    /* 0x10 */ LO *ploClone;   /* the indicator object spawned for it */
    /* 0x14 */ f32 tShown;
    /* 0x18 */ f32 s;
    /* 0x1C */ f32 dsdt;
    /* 0x20 */ QW pos;
};

/* An entry of the world's HUD blot table (0xC bytes, four of them from 0x3BA0): InitSwHudBlots fills the first word. */
struct HUDBLOT {
    /* 0x0 */ struct LO *plo; /* the blot object InitSwHudBlots found */
    /* 0x4 */ f32 velocity;   /* UpdateSwHudBlots: the smoothing velocity of the blot's value (GSmoothA's last argument) */
    /* 0x8 */ s32 fresh;      /* UpdateSwHudBlots: set while the blot is not drawn, then the next drawn frame jumps its value */
};

struct SW : BASIC {
    /* 0x10 */ DL field_0x10; /* Sw_Construct: InitDl ibDle 0x24 */
    u8 unknown_0x1C[0x4];
    /* 0x20 */ DL dlRoot;  /* the world's root objects: RemoveSwRoot (FFindDlEntry, RemoveDlEntry), ReinsertSwRoot (InsertDlEntryBefore), RemoveSwRootRaw (RemoveDlEntry) */
    /* 0x2C */ DL dlRootNext; /* PoxaAllocSw looks the object's proot up in it (FFindDlEntry); Sw_Construct: InitDl ibDle 0xC */
    u8 unknown_0x38[0x118]; /* Sw_Construct initialises 0x200 SLs from 0x38 (ibSle 0x1C) over state (0x150): a conflict, it goes through a view */
    /* 0x150 */ s32 state; /* FUpdateSwDuringWipe */
    u8 unknown_0x154[0x16E4];
    /* 0x1838 */ SL field_0x1838[0x200]; /* Sw_Construct: InitSl ibSle 0xC on each */
    /* 0x3038 */ SL aslCid[199]; /* one list of objects per class id, linked through LO::ploNextCid (InitSl ibSle 0x20): PdlFromSwCid,
                                    Sw_Construct, func_002102A0 */
    /* 0x398C */ SLOTHEAP field_0x398C; /* Sw_Construct: slots of 0x14 bytes, 0x100 per block */
    /* 0x39A4 */ void *field_0x39A4; /* RetractSwRoot: set to the root it moves when null */
    u8 unknown_0x39A8[0x28];
    /* 0x39D0 */ struct DCB *adcb; /* the object callback pool PdcbAllocSw hands out from (12-byte entries); func_0020E740 empties it */
    /* 0x39D4 */ s32 cdcb;         /* PdcbAllocSw: the next free entry */
    /* 0x39D8 */ struct OPTSET *aoptset; /* the option-set pool func_00210120 hands out from (12-byte entries); func_0020E740 empties it */
    /* 0x39DC */ s32 coptset;      /* func_00210120: the next free entry */
    /* 0x39E0 */ struct LO **pploPostLoadBegin; /* the objects PloNew queued for their PostLoad (slot 15): func_0020E740 calls it on each */
    /* 0x39E4 */ struct LO **pploPostLoadEnd;   /* PloNew appends at it; func_0020E740 resets it to pploPostLoadBegin after each pass */
    /* 0x39E8 */ struct BLOCK *pblockCur; /* func_001FFA40 */
    /* 0x39EC */ struct BLOCK *pblockFirst; /* the list of splice blocks, newest first (BLOCK::pnext): ReadSpliceBlock; one reader, SW is certain */
    /* 0x39F0 */ struct TIMEDCALL *ptimedcallFirst; /* the pending timed calls, func_00133130 */
    u8 unknown_0x39F4[0x8];
    /* 0x39FC */ SLOTHEAP slotheapTimedcall; /* their slot heap, func_00133130 */
    /* 0x3A14 */ s32 fRootFrame; /* InitSwRootFrame sets 1, ClearSwRootFrameFlag clears it */
    u8 unknown_0x3A18[0xE4];
    /* 0x3AFC */ s32 ctask; /* objects of class 0x85: func_00161660, func_001620B0, func_00162250, func_00165C98 */
    /* 0x3B00 */ DL field_0x3B00; /* Sw_Construct: InitDl ibDle 0x88 */
    /* 0x3B0C */ struct JOB *pjobCurrent; /* SetSwCurrentJob; func_001619A0, func_001649D0, func_0019D948 */
    /* 0x3B10 */ struct TASK *ptaskCurrent; /* SetSwCurrentTask, func_00163C28 */
    /* 0x3B14 */ struct TASK *ptaskRestart; /* SetSwRestartTask, func_00162A60 */
    /* 0x3B18 */ struct JOB *pjobPending; /* ShutdownSwForLoad ends it and clears it; bevy_jobs_162e38 tests it */
    /* 0x3B1C */ struct SAVEPATH *psavepathDt; /* save path "dt" (CreateSwSavePaths; the paths are PsavepathNew handles, passed on as int) */
    /* 0x3B20 */ struct SAVEPATH *psavepathCcoin; /* "loot/ccoin" */
    /* 0x3B24 */ struct SAVEPATH *psavepathWidCurrent; /* "widCurrent" */
    /* 0x3B28 */ struct SAVEPATH *psavepathEpisodeCurrent; /* "episodeCurrent" */
    /* 0x3B2C */ struct SAVEPATH *psavepathLang; /* "flags/lang"; ApplyOptionsFromSave reads 0x3B2C to 0x3B44 as the options */
    /* 0x3B30 */ struct SAVEPATH *psavepathMixerMode; /* "flags/nMixerMode" */
    /* 0x3B34 */ struct SAVEPATH *psavepathMusicVolume; /* "flags/uMusicVolume" */
    /* 0x3B38 */ struct SAVEPATH *psavepathEffectsVolume; /* "flags/uEffectsVolume" */
    /* 0x3B3C */ struct SAVEPATH *psavepathUseHeadset; /* "flags/fUseHeadset" */
    /* 0x3B40 */ struct SAVEPATH *psavepathDxScreenCenter; /* "flags/dxScreenCenter" */
    /* 0x3B44 */ struct SAVEPATH *psavepathDyScreenCenter; /* "flags/dyScreenCenter" */
    /* 0x3B48 */ struct SAVEPATH *psavepathNoVibration; /* "flags/fNoVibration" */
    /* 0x3B4C */ struct SAVEPATH *psavepathReverseLookAround; /* "flags/fReverseLookAround" */
    /* 0x3B50 */ struct SAVEPATH *psavepathReverseAim; /* "flags/fReverseAim" */
    /* 0x3B54 */ struct SAVEPATH *psavepathAutosaveWarned; /* "flags/fAutosaveWarned" */
    /* 0x3B58 */ struct SAVEPATH *apsavepathEpisodeDt[9]; /* "episode/<name>/dt" per episode */
    /* 0x3B7C */ struct SAVEPATH *apsavepathEpisodePercent[9]; /* "episode/<name>/percent_complete" per episode */
    /* 0x3BA0 */ HUDBLOT ahudblot[4]; /* InitSwHudBlots finds one blot object per entry (object ids D_002C3E70) and stores it in the first word */
    /* 0x3BD0 */ DL field_0x3BD0; /* Sw_Construct: InitDl ibDle 0xB4 */
    /* 0x3BDC */ SL field_0x3BDC; /* Sw_Construct: InitSl ibSle 0x4C */
    /* 0x3BE8 */ void *pfont; /* PostBlotLoad finds it once (object 0x374) when a blot needs it; func_00215AC0, func_00215BA8 read its word 0x54; func_00216BC8 */
    /* 0x3BEC */ s32 cblotActive; /* SetBlotBlots counts the blots of 16 frames or more that enter state 2 and up */
    /* 0x3BF0 */ s32 fLoadPending; /* SetSwLoadRequest sets it with the request */
    /* 0x3BF4 */ LOADREQ loadreq; /* SetSwLoadRequest copies one in whole */
    /* 0x3C40 */ LEVELID level; /* the current level: RequestTransition (through its SW argument), ActivateWipe (as B_003E10D0) */
    /* 0x3C80 */ s32 field_0x3C80; /* Sw_Construct sets -1 */
    /* 0x3C84 */ struct WARP *pwarpActive; /* Warp_SetState sets it when a warp starts (state 4) */
    /* 0x3C88 */ s32 field_0x3C88; /* func_00162A60 sets it to 0x189 when it restarts a task */
    /* 0x3C8C */ s32 field_0x3C8C; /* func_00162A60 sets it to -1 with 0x3C88 */
    /* 0x3C90 */ SLOTHEAP slotheapCb; /* the callbacks, func_00149B58 */
    /* 0x3CA8 */ struct CB *pcbFirst; /* func_00149B58 */
    /* 0x3CAC */ struct CB *pcbLast; /* func_00149B58 */
    u8 unknown_0x3CB0[0x4];
    /* 0x3CB4 */ SLOTHEAP field_0x3CB4; /* Sw_Construct: 0xC-byte slots, 0x200 per block */
    /* 0x3CCC */ s32 fAaoxDirty; /* UpdateSwAaox: tested and cleared before it sorts the object table */
    /* 0x3CD0 */ s32 cobr; /* PoxaAllocSw */
    /* 0x3CD4 */ struct OBR *aobr[3]; /* one per axis, PoxaAllocSw */
    /* 0x3CE0 */ SLOTHEAP slotheapOxa; /* PoxaAllocSw allocates an OXA (the contact record of the axis lists) from it; Sw_Construct: 0x80-byte slots */
    /* 0x3CF8 */ SLOTHEAP slotheapOx; /* AllocSwOx allocates a pair's node from it, UpdateSwPox frees them; Sw_Construct: 0x14-byte slots, 0x400 per block */
    /* 0x3D10 */ DL dlOxa; /* PoxaAllocSw appends the new OXA; RecalcSwOxfFilterForObject walks it (OXA link 0x48); Sw_Construct: InitDl ibDle 0x48 */
    /* 0x3D1C */ struct SWNODE *pnodeFirst; /* func_001F8F80 and IntersectSwBoundingSphere walk the list through SWNODE::pnext (0x40) */
    u8 unknown_0x3D20[0x8]; /* Sw_Construct initialises a DL at 0x3D1C (ibDle 0x40) whose head is pnodeFirst */
    /* 0x3D28 */ DL dlOxaRecalc; /* func_00133E30 (RecalcSwXpAll's first step) calls a virtual of each record's object until it is empty; Sw_Construct: InitDl ibDle 0x50 */
    /* 0x3D34 */ DL dlOxaDirty; /* RecalcSwXpAll settles and empties it (OXA link 0x58); Sw_Construct: InitDl ibDle 0x58 */
    /* 0x3D40 */ SLOTHEAP slotheapMq; /* CloneMqList */
    /* 0x3D58 */ s32 generation; /* func_00190D10 increments it */
    /* 0x3D5C */ s32 frame; /* func_001CD9E0 compares an SO stamp with it */
    /* 0x3D60 */ s32 field_0x3D60; /* func_001CDA80 counts its runs */
    /* 0x3D64 */ s32 frameLast; /* func_001CDA80 copies frame here when the two differ */
    /* 0x3D68 */ s32 idHitfxLast; /* func_00156548 increments it for each new hit effect */
    u8 unknown_0x3D6C[0x4];
    /* 0x3D70 */ s32 stamp; /* func_001C1968 */
    /* 0x3D74 */ s32 pzlinkChange; /* AddPzlinkHierarchy and RemovePzlinkHierarchy (PZLINK slots 11 and 12) agree: each adds 1 and copies it to ppzgraph->stamp */
    /* 0x3D78 */ s32 chandsOff;    /* SetHandsOff (+1; the first one calls AddGrfusr(2)), ClearHandsOff (-1; the last one calls RemoveGrfusr(2)),
                                      FSwHandsOff (> 0) */
    /* 0x3D7C */ s32 chandsOffSw;  /* IncrementSwHandsOff (+1; the first one calls AddGrfusr(4)), DecrementSwHandsOff (-1; the last one calls
                                      RemoveGrfusr(4)) */
    /* 0x3D80 */ s32 cshow; /* IncrementSwShowCount, DecrementSwShowCount: the shows in progress; the world's show object is started at 1 and stopped at 0 */
    /* 0x3D84 */ s32 cbinoc; /* IncrementSwBinocCount, DecrementSwBinocCount, FSwBinocActive (> 0) */
    /* 0x3D88 */ DL dlAsega; /* UpdateSw walks it with UpdateAsega; Sw_Construct initialises it with ibDle 0x24 */
    /* 0x3D94 */ SLOTHEAP field_0x3D94; /* Sw_Construct: 0x60-byte slots */
    /* 0x3DAC */ SLOTHEAP field_0x3DAC; /* Sw_Construct: 0x80-byte slots */
    /* 0x3DC4 */ SLOTHEAP field_0x3DC4; /* Sw_Construct: 0x14-byte slots, 8 per block */
    /* 0x3DDC */ DL field_0x3DDC; /* Sw_Construct: InitDl ibDle 0x1C */
    /* 0x3DE8 */ SLOTHEAP field_0x3DE8; /* Sw_Construct: 0x50-byte slots */
    /* 0x3E00 */ s32 field_0x3E00; /* Sw_Construct sets 0x80000000 */
    u8 unknown_0x3E04[0xC];
    /* 0x3E10 */ QW hsvFog; /* SetSwFogHsv; UpdateSwFog converts it (hue, saturation and value in 0..255) */
    /* 0x3E20 */ f32 scaleFog; /* func_0020F2F8; UpdateSwFog scales the fog colour by it / 255 */
    /* 0x3E24 */ f32 alphaFog; /* func_0020F2D8; UpdateSwFog turns it into the fog alpha */
    /* 0x3E28 */ u8 vifParams[0x10]; /* reader: FlushRenderRecords (unpacked as one quadword to VU1 row 10) */
    /* 0x3E38 */ s32 field_0x3E38; /* AllocSwBuffers sets it when the load request has bit 0x20; UpdateCmLast, RestartAtTask test it */
    /* 0x3E3C */ s32 fDirectPacket; /* reader: FlushRenderRecords (nonzero: send the 0x25 direct packet) */
    u8 unknown_0x3E40[0x4];
    /* 0x3E44 */ SLOTHEAP field_0x3E44; /* Sw_Construct: 0x30-byte slots */
    u8 unknown_0x3E5C[0x4];
    /* 0x3E60 */ s32 field_0x3E60; /* WarpJtToSafePoint passes it to StartFade */
    /* 0x3E64 */ f32 field_0x3E64; /* Sw_Construct sets 128 */
    /* 0x3E68 */ f32 field_0x3E68; /* Sw_Construct sets 96 */
    /* 0x3E6C */ f32 field_0x3E6C; /* Sw_Construct sets 160 */
    u8 unknown_0x3E70[0x30];
    /* 0x3EA0 */ u64 gs; /* a GS register value, func_001EA9F0 */
    /* 0x3EA8 */ s32 fGsDirty; /* readers: FlushRenderRecords (clears it, then func_001EA9F0), fun_00210978 */
    /* 0x3EAC */ struct JOY *pvjoyFirst; /* a list linked at 0x84: UpdateSw calls UpdateVjoy on each; Sw_Construct's InitSl gives the link */
    u8 unknown_0x3EB0[0x8];
    /* 0x3EB8 */ s32 clo; /* func_001C4AF8 */
    /* 0x3EBC */ struct LO *aplo[16]; /* func_001C4AF8; at most 16 (the focus follows at 0x3EFC) */
    /* 0x3EFC */ struct PO *ppoFocusBase; /* SetSwFocusBase, SetSwFocusOverride */
    /* 0x3F00 */ struct PO *ppoFocusOverride; /* SetSwFocusBase, SetSwFocusOverride */
    /* 0x3F04 */ s32 ccloneset; /* InitCloneSets */
    /* 0x3F08 */ struct CLONESET *acloneset; /* InitCloneSets, InstantiateClone */
    /* 0x3F0C */ struct SCOPE *pscopeDefault; /* used when the context object has none: RefOpFindObject, func_001241E8, func_00124578, RefOpFindNearestObject; AllocSwBuffers allocates it */
    /* 0x3F10 */ s32 field_0x3F10; /* Sw_Construct sets it to -2 */
    /* 0x3F14 */ s32 cgrfentry; /* AddSwGrfEntry, SolveSw, func_001CDA80 */
    /* 0x3F18 */ s32 cgrfentryDead; /* AddSwGrfEntry compacts the table when they pass a tenth */
    /* 0x3F1C */ s32 *pigrfentryRunning; /* the loop index of the walk in progress, which AddSwGrfEntry fixes up (SolveSw, func_001CDA80) */
    /* 0x3F20 */ GRFENTRY *agrfentry; /* AddSwGrfEntry, SolveSw, func_001CDA80 */
    /* 0x3F24 */ DL field_0x3F24; /* Sw_Construct: InitDl ibDle 0xE0 */
    /* 0x3F30 */ DL field_0x3F30; /* Sw_Construct: InitDl ibDle 0x1B4 */
    /* 0x3F3C */ DL field_0x3F3C; /* Sw_Construct: InitDl ibDle 0x1B4 */
    /* 0x3F48 */ DL field_0x3F48; /* Sw_Construct: InitDl ibDle 0x104 */
    /* 0x3F54 */ DL field_0x3F54; /* Sw_Construct: InitDl ibDle 0x174 */
    /* 0x3F60 */ DL field_0x3F60; /* Sw_Construct: InitDl ibDle 0x1B4 */
    /* 0x3F6C */ DL field_0x3F6C; /* Sw_Construct: InitDl ibDle 0x104 */
    /* 0x3F78 */ DL field_0x3F78; /* Sw_Construct: InitDl ibDle 0x104 */
    /* 0x3F84 */ DL field_0x3F84; /* Sw_Construct: InitDl ibDle 0x104 */
    /* 0x3F90 */ DL field_0x3F90; /* Sw_Construct: InitDl ibDle 0xE0 */
    /* 0x3F9C */ DL field_0x3F9C; /* Sw_Construct: InitDl ibDle 0x100 */
    /* 0x3FA8 */ DL field_0x3FA8; /* Sw_Construct: InitDl ibDle 0x154 */
    /* 0x3FB4 */ DL field_0x3FB4; /* Sw_Construct: InitDl ibDle 0xFE0 */
    /* 0x3FC0 */ DL field_0x3FC0; /* Sw_Construct: InitDl ibDle 0x174 */
    /* 0x3FCC */ DL field_0x3FCC; /* Sw_Construct: InitDl ibDle 0x20 */
    /* 0x3FD8 */ DL field_0x3FD8; /* Sw_Construct: InitDl ibDle 0x104 */
    /* 0x3FE4 */ DL field_0x3FE4; /* Sw_Construct: InitDl ibDle 0xE0 */
    /* 0x3FF0 */ DL field_0x3FF0; /* Sw_Construct: InitDl ibDle 0x130 */
    /* 0x3FFC */ DL dlHitfx; /* func_00156548 */
    /* 0x4008 */ SLOTHEAP slotheapHitfx; /* func_00156548 */
    /* 0x4020 */ struct BASIC *phitfxdef; /* func_0017A7F8 hands it to PhitfxSpawn, whose Splice binding passes a BASIC */
    /* 0x4024 */ struct BASIC *phitfxdefB; /* SpawnSwHitFx (kind 1) and ReplaceSwHitFx (side 1) pass it as phitfxdef is for kind 0 / side 0: two readers agree */
    /* 0x4028 */ void *field_0x4028; /* GoalAnimLeap_FHandleMessage: the first argument of PhitfxSpawn, as phitfxdef (0x4020) and field_0x402C are for others */
    /* 0x402C */ s32 field_0x402C; /* ExplodeGadgetBurst passes it to PhitfxSpawn (a hit effect id/def) */
    u8 unknown_0x4030[0xC];
    /* 0x403C */ SLOTHEAP slotheapRipg; /* PripgNew */
    /* 0x4054 */ SLOTHEAP slotheapRip; /* PripNewRipg */
    /* 0x406C */ struct PRIPG *pripgCached; /* PripgNew */
    /* 0x4070 */ SLOTHEAP slotheapBlipg; /* PblipgNew */
    /* 0x4088 */ SLOTHEAP slotheapBlip; /* the blips: PblipNew allocates one; Sw_Construct creates it (0x10C0-byte slots), func_0020E740 primes it */
    /* 0x40A0 */ SLOTHEAP slotheapBlipSp; /* the sprite data of a blip of mode 2: PblipNew allocates it, Sw_Construct creates it (0x560-byte slots) */
    /* 0x40B8 */ SLOTHEAP field_0x40B8; /* Sw_Construct: 0x1C-byte slots */
    /* 0x40D0 */ SLOTHEAP field_0x40D0; /* Sw_Construct: 0xF0-byte slots */
    /* 0x40E8 */ SLOTHEAP slotheapXa; /* the XA records: PxaAllocSw, FreeSwXaList; Sw_Construct: 0x10-byte slots */
    /* 0x4100 */ SL field_0x4100; /* Sw_Construct: InitSl ibSle 0x18 */
    /* 0x410C */ SL field_0x410C; /* Sw_Construct: InitSl ibSle 0x40 */
    /* 0x4118 */ SLOTHEAP slotheapWkr; /* ExpireSwWkrs */
    /* 0x4130 */ DL dlWkr; /* ExpireSwWkrs */
    /* 0x413C */ SLOTHEAP field_0x413C; /* Sw_Construct: 0x30-byte slots */
    /* 0x4154 */ struct LIGHT *aplight[0x100]; /* RemoveLightFromSw clears a light's slot, func_001A3EE8 walks them (AddLightToSw adds each) */
    /* 0x4554 */ s32 fLightsDirty;         /* RemoveLightFromSw sets it, func_001A3EE8 clears it and rebuilds the light sets */
    /* 0x4558 */ s32 cbspnode; /* func_0013E0E0 */
    /* 0x455C */ struct BSPNODE *abspnode; /* func_0013E0E0 */
    /* 0x4560 */ s32 cregion; /* func_0013E0E0 */
    /* 0x4564 */ void *aregion; /* func_0013E0E0 (0x20-byte elements) */
    u8 unknown_0x4568[0x8];
    /* 0x4570 */ u8 setLightsGlobal[0x20];  /* func_001A3EE8 clears it before it re-adds the lights */
    /* 0x4590 */ u32 grfLightSlotFree[8];   /* RemoveLightFromSw sets the bit of a freed light slot */
    /* 0x45B0 */ DL field_0x45B0; /* Sw_Construct: InitDl ibDle 0x1D0 */
    /* 0x45BC */ DL field_0x45BC; /* Sw_Construct: InitDl ibDle 0x1E0 */
    /* 0x45C8 */ struct LO *ploPathzoneDefault; /* func_001C10C8 creates the default pathzone (PloNew class 0x11) and keeps it here until the graph exists */
    /* 0x45CC */ struct PZGRAPH *ppzgraph; /* AddSoLoHierarchy */
    /* 0x45D0 */ f32 field_0x45D0[3]; /* Sw_Construct: a slope and offset from the constants D_002C3E60 to D_002C3E6C, then 0 */
    u8 unknown_0x45DC[0x4];
    /* 0x45E0 */ f32 field_0x45E0[2]; /* Sw_Construct: D_002C3E6C and D_002C3E68 */
    /* 0x45E8 */ struct ZPRENTRY azprentry[2]; /* AllocSwBuffers fills each with func_001BE398 and a fresh ZPR */
    /* 0x4638 */ void *ppool; /* func_0013CF38 */
    /* 0x463C */ u32 oidNext; /* reader: PostCrfodbLoad hands out the next object id from it (certain: read through the global) */
    /* 0x4640 */ s32 field_0x4640; /* func_00210BE0, func_00211EC0 test it; LoadSwStringsFromBrx stores the string count */
    /* 0x4644 */ struct SWSTRING *astring; /* LoadSwStringsFromBrx: the string table, cstring (0x4640) entries of 8 bytes */
    /* 0x4648 */ SLOTHEAP field_0x4648; /* Sw_Construct: 0x40-byte slots */
    /* 0x4660 */ SLOTHEAP field_0x4660; /* Sw_Construct: 0xD0-byte slots */
    /* 0x4678 */ s32 ctgt; /* the target list's length: UpdateSwTargetList */
    u8 unknown_0x467C[0x4];
    /* 0x4680 */ TGT atgt[4]; /* the target list: UpdateSwTargetList */
    /* 0x4740 */ s32 field_0x4740; /* Sw_Construct sets -1 */
    /* 0x4744 */ struct LO *ploIndicatorTemplate; /* reader: FindTargetIndicatorTemplate (stores PloFindSwObject_thunk's result), func_00195608 hands it to PloSpawnTargetIndicator */
    /* 0x4748 */ s32 fGuardsFrozen; /* SetSwGuardsFrozen */
    /* 0x474C */ f32 tGuardsFrozen; /* SetSwGuardsFrozen */
    /* 0x4750 */ f32 field_0x4750; /* Sw_Construct sets -60, as it sets tL3; UpdateCplook reads it through a local view (tLook) */
    /* 0x4754 */ f32 tL3; /* func_00140338 */
    u8 unknown_0x4758[0x4];
    /* 0x475C */ f32 sTimeScale; /* StartSwAmbSfx adds it to the pitch */
    u8 unknown_0x4760[0x4];
    /* 0x4764 */ s32 cclueFound; /* InitSwHudBlots stores CcluesFound() */
    /* 0x4768 */ s32 field_0x4768; /* InitSwHudBlots stores func_001C7D00()'s result */
    /* 0x476C */ f32 tEmit; /* HideCountdownBlot clears it; UpdateSwHudBlots */
    /* 0x4770 */ s32 emitStamp; /* UpdateSwHudBlots: the last whole second it played an emitter for */
    /* 0x4774 */ struct TARGET *ptarget; /* func_0015DA88 */
    /* 0x4778 */ s32 cemitter; /* func_001C4848 (adds an emitter, at most 4), func_001C48C0 (walks them): two readers that agree */
    /* 0x477C */ struct EMITTER *aemitter[4]; /* the same two: the emitters the focus changes make follow it */
    u8 unknown_0x478C[0x4];
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(SW, astring, 0x4644);
SLY2_OFFSET_CHECK(SW, field_0x4028, 0x4028);
SLY2_OFFSET_CHECK(SW, field_0x402C, 0x402C);
SLY2_SIZE_CHECK(SLOTHEAP, 0x18);
SLY2_SIZE_CHECK(LOADREQ, 0x4C);
SLY2_SIZE_CHECK(LEVELID, 0x40);
SLY2_OFFSET_CHECK(SW, level, 0x3C40);
SLY2_SIZE_CHECK(GRFENTRY, 0x8);
SLY2_SIZE_CHECK(TGT, 0x30);
SLY2_SIZE_CHECK(SW, 0x4790);
SLY2_SIZE_CHECK(HUDBLOT, 0xC);
SLY2_OFFSET_CHECK(SW, ahudblot, 0x3BA0);
SLY2_OFFSET_CHECK(SW, cshow, 0x3D80);
SLY2_OFFSET_CHECK(SW, cbinoc, 0x3D84);
SLY2_OFFSET_CHECK(SW, hsvFog, 0x3E10);
SLY2_OFFSET_CHECK(SW, scaleFog, 0x3E20);
SLY2_OFFSET_CHECK(SW, alphaFog, 0x3E24);
SLY2_OFFSET_CHECK(SW, cclueFound, 0x4764);
SLY2_OFFSET_CHECK(SW, state, 0x150);
SLY2_OFFSET_CHECK(SW, aslCid, 0x3038);
SLY2_OFFSET_CHECK(SW, field_0x39A4, 0x39A4);
SLY2_OFFSET_CHECK(SW, adcb, 0x39D0);
SLY2_OFFSET_CHECK(SW, coptset, 0x39DC);
SLY2_OFFSET_CHECK(SW, pploPostLoadBegin, 0x39E0);
SLY2_OFFSET_CHECK(SW, pploPostLoadEnd, 0x39E4);
SLY2_OFFSET_CHECK(SW, pjobPending, 0x3B18);
SLY2_OFFSET_CHECK(SW, pfont, 0x3BE8);
SLY2_OFFSET_CHECK(SW, pzlinkChange, 0x3D74);
SLY2_OFFSET_CHECK(SW, chandsOff, 0x3D78);
SLY2_OFFSET_CHECK(SW, chandsOffSw, 0x3D7C);
SLY2_OFFSET_CHECK(SW, slotheapBlip, 0x4088);
SLY2_OFFSET_CHECK(SW, slotheapBlipSp, 0x40A0);
SLY2_OFFSET_CHECK(SW, aplight, 0x4154);
SLY2_OFFSET_CHECK(SW, fLightsDirty, 0x4554);
SLY2_OFFSET_CHECK(SW, setLightsGlobal, 0x4570);
SLY2_OFFSET_CHECK(SW, grfLightSlotFree, 0x4590);
SLY2_OFFSET_CHECK(SW, ploPathzoneDefault, 0x45C8);
SLY2_OFFSET_CHECK(SW, azprentry, 0x45E8);
SLY2_OFFSET_CHECK(SW, pblockCur, 0x39E8);
SLY2_OFFSET_CHECK(SW, fAaoxDirty, 0x3CCC);
SLY2_OFFSET_CHECK(SW, ptimedcallFirst, 0x39F0);
SLY2_OFFSET_CHECK(SW, slotheapTimedcall, 0x39FC);
SLY2_OFFSET_CHECK(SW, ctask, 0x3AFC);
SLY2_OFFSET_CHECK(SW, pjobCurrent, 0x3B0C);
SLY2_OFFSET_CHECK(SW, ptaskCurrent, 0x3B10);
SLY2_OFFSET_CHECK(SW, ptaskRestart, 0x3B14);
SLY2_OFFSET_CHECK(SW, psavepathDt, 0x3B1C);
SLY2_OFFSET_CHECK(SW, psavepathCcoin, 0x3B20);
SLY2_OFFSET_CHECK(SW, psavepathWidCurrent, 0x3B24);
SLY2_OFFSET_CHECK(SW, psavepathEpisodeCurrent, 0x3B28);
SLY2_OFFSET_CHECK(SW, psavepathLang, 0x3B2C);
SLY2_OFFSET_CHECK(SW, psavepathMixerMode, 0x3B30);
SLY2_OFFSET_CHECK(SW, psavepathMusicVolume, 0x3B34);
SLY2_OFFSET_CHECK(SW, psavepathEffectsVolume, 0x3B38);
SLY2_OFFSET_CHECK(SW, psavepathUseHeadset, 0x3B3C);
SLY2_OFFSET_CHECK(SW, psavepathDxScreenCenter, 0x3B40);
SLY2_OFFSET_CHECK(SW, psavepathDyScreenCenter, 0x3B44);
SLY2_OFFSET_CHECK(SW, psavepathNoVibration, 0x3B48);
SLY2_OFFSET_CHECK(SW, psavepathReverseLookAround, 0x3B4C);
SLY2_OFFSET_CHECK(SW, psavepathReverseAim, 0x3B50);
SLY2_OFFSET_CHECK(SW, psavepathAutosaveWarned, 0x3B54);
SLY2_OFFSET_CHECK(SW, apsavepathEpisodeDt, 0x3B58);
SLY2_OFFSET_CHECK(SW, apsavepathEpisodePercent, 0x3B7C);
SLY2_OFFSET_CHECK(SW, cblotActive, 0x3BEC);
SLY2_OFFSET_CHECK(SW, fLoadPending, 0x3BF0);
SLY2_OFFSET_CHECK(SW, loadreq, 0x3BF4);
SLY2_OFFSET_CHECK(SW, field_0x3C88, 0x3C88);
SLY2_OFFSET_CHECK(SW, field_0x3C8C, 0x3C8C);
SLY2_OFFSET_CHECK(SW, slotheapCb, 0x3C90);
SLY2_OFFSET_CHECK(SW, pcbFirst, 0x3CA8);
SLY2_OFFSET_CHECK(SW, pcbLast, 0x3CAC);
SLY2_OFFSET_CHECK(SW, cobr, 0x3CD0);
SLY2_OFFSET_CHECK(SW, aobr, 0x3CD4);
SLY2_OFFSET_CHECK(SW, pnodeFirst, 0x3D1C);
SLY2_OFFSET_CHECK(SW, slotheapMq, 0x3D40);
SLY2_OFFSET_CHECK(SW, generation, 0x3D58);
SLY2_OFFSET_CHECK(SW, frame, 0x3D5C);
SLY2_OFFSET_CHECK(SW, field_0x3D60, 0x3D60);
SLY2_OFFSET_CHECK(SW, frameLast, 0x3D64);
SLY2_OFFSET_CHECK(SW, idHitfxLast, 0x3D68);
SLY2_OFFSET_CHECK(SW, stamp, 0x3D70);
SLY2_OFFSET_CHECK(SW, field_0x3E38, 0x3E38);
SLY2_OFFSET_CHECK(SW, dlRoot, 0x20);
SLY2_OFFSET_CHECK(SW, dlAsega, 0x3D88);
SLY2_OFFSET_CHECK(SW, gs, 0x3EA0);
SLY2_OFFSET_CHECK(SW, pvjoyFirst, 0x3EAC);
SLY2_OFFSET_CHECK(SW, clo, 0x3EB8);
SLY2_OFFSET_CHECK(SW, aplo, 0x3EBC);
SLY2_OFFSET_CHECK(SW, ppoFocusBase, 0x3EFC);
SLY2_OFFSET_CHECK(SW, ppoFocusOverride, 0x3F00);
SLY2_OFFSET_CHECK(SW, ccloneset, 0x3F04);
SLY2_OFFSET_CHECK(SW, acloneset, 0x3F08);
SLY2_OFFSET_CHECK(SW, pscopeDefault, 0x3F0C);
SLY2_OFFSET_CHECK(SW, field_0x3F10, 0x3F10);
SLY2_OFFSET_CHECK(SW, cgrfentry, 0x3F14);
SLY2_OFFSET_CHECK(SW, cgrfentryDead, 0x3F18);
SLY2_OFFSET_CHECK(SW, pigrfentryRunning, 0x3F1C);
SLY2_OFFSET_CHECK(SW, agrfentry, 0x3F20);
SLY2_OFFSET_CHECK(SW, dlHitfx, 0x3FFC);
SLY2_OFFSET_CHECK(SW, slotheapHitfx, 0x4008);
SLY2_OFFSET_CHECK(SW, phitfxdef, 0x4020);
SLY2_OFFSET_CHECK(SW, slotheapRipg, 0x403C);
SLY2_OFFSET_CHECK(SW, slotheapRip, 0x4054);
SLY2_OFFSET_CHECK(SW, pripgCached, 0x406C);
SLY2_OFFSET_CHECK(SW, slotheapBlipg, 0x4070);
SLY2_OFFSET_CHECK(SW, slotheapWkr, 0x4118);
SLY2_OFFSET_CHECK(SW, dlWkr, 0x4130);
SLY2_OFFSET_CHECK(SW, cbspnode, 0x4558);
SLY2_OFFSET_CHECK(SW, abspnode, 0x455C);
SLY2_OFFSET_CHECK(SW, cregion, 0x4560);
SLY2_OFFSET_CHECK(SW, aregion, 0x4564);
SLY2_OFFSET_CHECK(SW, ppzgraph, 0x45CC);
SLY2_OFFSET_CHECK(SW, ppool, 0x4638);
SLY2_OFFSET_CHECK(SW, field_0x4640, 0x4640);
SLY2_OFFSET_CHECK(SW, ctgt, 0x4678);
SLY2_OFFSET_CHECK(SW, atgt, 0x4680);
SLY2_OFFSET_CHECK(SW, fGuardsFrozen, 0x4748);
SLY2_OFFSET_CHECK(SW, tGuardsFrozen, 0x474C);
SLY2_OFFSET_CHECK(SW, pwarpActive, 0x3C84);
SLY2_OFFSET_CHECK(SW, tL3, 0x4754);
SLY2_OFFSET_CHECK(SW, sTimeScale, 0x475C);
SLY2_OFFSET_CHECK(SW, ptarget, 0x4774);
SLY2_OFFSET_CHECK(SW, field_0x1838, 0x1838);
SLY2_OFFSET_CHECK(SW, field_0x3E64, 0x3E64);
SLY2_OFFSET_CHECK(SW, field_0x3FF0, 0x3FF0);
SLY2_OFFSET_CHECK(SW, field_0x45E0, 0x45E0);
SLY2_OFFSET_CHECK(SW, field_0x4660, 0x4660);
SLY2_OFFSET_CHECK(SW, field_0x4750, 0x4750);
SLY2_OFFSET_CHECK(SW, dlRootNext, 0x2C);
SLY2_OFFSET_CHECK(SW, pblockFirst, 0x39EC);
SLY2_OFFSET_CHECK(SW, fRootFrame, 0x3A14);
SLY2_OFFSET_CHECK(SW, slotheapOxa, 0x3CE0);
SLY2_OFFSET_CHECK(SW, dlOxaDirty, 0x3D34);
SLY2_OFFSET_CHECK(SW, fDirectPacket, 0x3E3C);
SLY2_OFFSET_CHECK(SW, fGsDirty, 0x3EA8);
SLY2_OFFSET_CHECK(SW, phitfxdefB, 0x4024);
SLY2_OFFSET_CHECK(SW, slotheapXa, 0x40E8);
SLY2_OFFSET_CHECK(SW, tEmit, 0x476C);
#endif
#endif
