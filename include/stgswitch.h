/* SPDX-License-Identifier: GPL-3.0-or-later */
/* STGSWITCH, the staged switch object (the Stg functions of src/mpeg-memcard/): an LO that steps through a list of stage nodes, each
   holding a list of actions. Layout from RunStgSwitch (reads istage, cstage, anode, ploHit, kind) and the writers AddStgSwitchStage,
   SetStgSwitchHitter and SetStgSwitchStageHits (two or more functions agree on each field below). C++ only. */
#ifndef SLY2_STGSWITCH_H
#define SLY2_STGSWITCH_H
#include "lo.h"

/* One stage, 0x10 bytes: AddStgSwitchStage fills id, fForward and the action list (room for 0x20 words); RunStgSwitch reads fForward and count. */
struct STGNODE {
    s32 id;       /* AddStgSwitchStage, RunStgSwitch */
    s32 fForward; /* AddStgSwitchStage sets 1, SetStgSwitchStageHits sets the hit count, RunStgSwitch */
    s32 count;
    void *ents;   /* AddStgSwitchStage allocates it from the allocation stack */
};

struct STGSWITCH : LO {
    u8 unknown_0x50[0x10C];
    /* 0x15C */ s32 istage;     /* AddStgSwitchStage copies the stage count into it; SetStgSwitchStageHits tests -1; RunStgSwitch */
    /* 0x160 */ s32 cstage;     /* AddStgSwitchStage counts up to 0x20; RunStgSwitch */
    /* 0x164 */ STGNODE *anode; /* AddStgSwitchStage, RunStgSwitch */
    u8 unknown_0x168[0x4];
    /* 0x16C */ LO *ploHit;     /* SetStgSwitchHitter, RunStgSwitch */
    /* 0x170 */ s32 kind;       /* SetStgSwitchHitter, RunStgSwitch */
};
#endif
