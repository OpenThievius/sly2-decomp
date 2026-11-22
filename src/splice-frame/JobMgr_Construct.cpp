// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"

struct SAVE;
struct DIFFICULTY;

/* the job manager, 0x1C bytes (JobMgr_Construct clears it, then sets three ids to -1; our name) */
struct JOBMGR {
    u8 unknown_0x0[0x10];
    /* 0x10 */ s32 field_0x10; /* JobMgr_Construct sets -1 */
    /* 0x14 */ s32 field_0x14; /* same */
    /* 0x18 */ s32 field_0x18; /* same */
};

void OnDifficultyGameLoad(DIFFICULTY *);
extern "C" {
void ResetSaveKeepingOptions(SAVE *, s32);
extern SAVE B_003D4A60;
extern DIFFICULTY B_002DE578;
extern s32 g_2e1e00;

void JobMgr_Construct(JOBMGR *pjobmgr) {
    memset(pjobmgr, 0, 0x1C);
    pjobmgr->field_0x10 = -1;
    pjobmgr->field_0x14 = -1;
    pjobmgr->field_0x18 = -1;
    ResetSaveKeepingOptions(&B_003D4A60, 0);
    OnDifficultyGameLoad(&B_002DE578);
    g_2e1e00 = 0;
}

}
