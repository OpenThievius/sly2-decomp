/* SPDX-License-Identifier: GPL-3.0-or-later */
/* STGSWITCH, the staged switch object (the Stg functions of src/mpeg-memcard/): an LO that steps through a list of stage nodes, each
   holding a list of actions. Layout from RunStgSwitch (reads istage, cstage, anode, ploHit, kind) and the writers AddStgSwitchStage,
   SetStgSwitchHitter and SetStgSwitchStageHits (two or more functions agree on each field below). C++ only. */
#ifndef SLY2_STGSWITCH_H
#define SLY2_STGSWITCH_H
#include "lo.h"

/* One action of a stage (8 bytes): StepStgSwitch runs it forward or backward by kind (0 and 1 Add and Remove an object found by arg,
   2 to 5 call the stage helpers), LoadStgSwitchFromBrx copies the kind 0xC ones' payload. */
struct STGENT {
    s32 kind;
    union {
        s32 arg;  /* kinds 0 to 5: the object's oid or the helper's argument */
        void *pv; /* kind 0xC: a payload LoadStgSwitchFromBrx copies */
    };
};
/* One class a hitter may be of (8 bytes): AddStgSwitchClass appends, func_001BADF0 matches the toucher against cid. */
struct STGCLASS {
    s32 cid;
    s32 field_0x4;
};

/* One stage, 0x10 bytes: AddStgSwitchStage fills id, fForward and the action list (room for 0x20 words); RunStgSwitch reads fForward and count. */
struct STGNODE {
    s32 id;       /* AddStgSwitchStage, RunStgSwitch */
    s32 fForward; /* AddStgSwitchStage sets 1, SetStgSwitchStageHits sets the hit count, RunStgSwitch */
    s32 count;
    union {
        void *ents;       /* AddStgSwitchStage allocates it from the allocation stack */
        STGENT *aent;     /* the same word as its array of actions: StepStgSwitch, LoadStgSwitchFromBrx */
    };
};

struct STGSWITCH : LO {
    u8 unknown_0x50[0x100];
    /* 0x150 */ s32 cclass;     /* reader: AddStgSwitchClass (up to 8), func_001BADF0, LoadStgSwitchFromBrx (copies cclass * 8 bytes of aclass) */
    /* 0x154 */ STGCLASS *aclass; /* the same three */
    /* 0x158 */ s32 fPending;   /* reader: StepStgSwitch (a method of STGSWITCH) clears it once the stages have run */
    /* 0x15C */ s32 istage;     /* AddStgSwitchStage copies the stage count into it; SetStgSwitchStageHits tests -1; RunStgSwitch */
    /* 0x160 */ s32 cstage;     /* AddStgSwitchStage counts up to 0x20; RunStgSwitch */
    /* 0x164 */ STGNODE *anode; /* AddStgSwitchStage, RunStgSwitch */
    u8 unknown_0x168[0x4];
    /* 0x16C */ LO *ploHit;     /* SetStgSwitchHitter, RunStgSwitch */
    /* 0x170 */ s32 kind;       /* SetStgSwitchHitter, RunStgSwitch */
};
#endif
