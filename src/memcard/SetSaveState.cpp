// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "types.h"

#include "memcard.h"





struct UL { long v; } __attribute__((packed));
struct MENU { char pad[0x44]; int phase; };
extern "C" {
#include "sw.h"
extern SW B_003DD490;
extern MENU B_002E6550;
extern char B_002E65A0[];
extern float g_2dded0[];
extern const UL g_2a6ba0;
extern const UL g_2a6ba8;
void func_001ACC38(MENU *, int);
int BusyMenu_FShowing(void *);
void BusyMenu_Hide(void *);
void MemcardMenu_SetState(MENU *, int);
void CreateMemcardThread__FP7MEMCARDii(MEMCARD *, long);
CRef RefGetGameSaveValue(void *, void *);
void ResetSaveKeepingOptions(SLOT *, int);
int CompareSaves__FP4SAVET0(MCFILEINFO *, MCFILEINFO *);
}

void SetSaveState(SAVE *psave, int nState)
{
    if (nState == psave->state) return;
    if (psave->state == 6) {
        psave->pslotNewest = 0;
        if (psave->pslotCur != 0 && B_002E6550.phase == 1) {
            func_001ACC38(&B_002E6550, 3);
            if (BusyMenu_FShowing(B_002E65A0) != 0) {
                MemcardMenu_SetState(&B_002E6550, 0x23);
                BusyMenu_Hide(B_002E65A0);
            } else {
                MemcardMenu_SetState(&B_002E6550, 0x24);
            }
        }
    }
    switch (nState) {
    case 0:
    case 1:
        CreateMemcardThread__FP7MEMCARDii(&psave->mc, g_2a6ba0.v);
        break;
    case 3:
        CreateMemcardThread__FP7MEMCARDii(&psave->mc, g_2a6ba8.v);
        break;
    case 6:
        psave->pslotNewest = &psave->aslot[0];
        for (int islot = 0; islot < 3; islot++) {
            SLOT *pslot = &psave->aslot[islot];
            float dt = RefGetGameSaveValue(B_003DD490.psavepathDt, pslot).m_tag.m_g;
            if (dt != 0.0f) {
                if (CompareSaves__FP4SAVET0(&psave->pslotNewest->info, &pslot->info) < 0)
                    psave->pslotNewest = pslot;
            } else {
                ResetSaveKeepingOptions(pslot, 0);
            }
        }
        break;
    }
    psave->state = nState;
    psave->tStamp = g_2dded0[15];
}
