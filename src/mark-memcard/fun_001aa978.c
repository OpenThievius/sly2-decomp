/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "memcard.h"

struct JOBMGR;

void InitSave(SAVE *psave, s32 port, s32 slot);
void JobMgr_Construct(struct JOBMGR *pjobmgr);
extern struct JOBMGR B_002DEB30;
extern SAVE B_002E65E0;
extern s32 B_004425D8;

void func_001AA978(void) {
    JobMgr_Construct(&B_002DEB30);
    B_004425D8 = -1;
    InitSave(&B_002E65E0, 0, 0);
}
