// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "sw.h"

struct STGNODE { int id; int fForward; int count; void *ents; };
struct STGPART { int unknown; int active; };
struct STGSWITCH : LO {
    u8 unknown_0x50[0x100];
    /* 0x150 */ int cpart;
    /* 0x154 */ STGPART *apart;
    /* 0x158 */ int cframe;
    /* 0x15C */ int istage;
    /* 0x160 */ int cstage;
    /* 0x164 */ STGNODE *anode;
    /* 0x168 */ int grfFx;
    /* 0x16C */ LO *ploHit;
    /* 0x170 */ int kind;
};

extern "C" {
int FStgSwitchDone(STGSWITCH *);
int FIsBasicDerivedFrom(LO *, int);
PO *PpoSwFocusBase(SW *);
void RunStgSwitchStage(STGSWITCH *, STGNODE *);
int FStgSwitchInStageRange(STGSWITCH *);
QW PosLoWorld(LO *);
void SpawnSwHitFx(SW *, int, QW, LO *);
void bevy_camera_follow_activity(void *, int, void *);
extern SW B_003DD490;
extern char B_002DEB30[];

void RunStgSwitch(STGSWITCH *psw)
{
    if (FStgSwitchDone(psw) != 0)
        return;
    if (psw->ploHit == (LO *)PpoSwFocusBase(&B_003DD490)) {
        psw->grfFx = 0xE;
    } else if (psw->kind == 0x100 || psw->kind == 0x10000) {
        psw->grfFx = 8;
    } else if (psw->kind == 0x20000) {
        psw->grfFx = 8;
    } else if (psw->ploHit == 0) {
        psw->grfFx = 0;
    } else if (FIsBasicDerivedFrom(psw->ploHit, 0x3B) != 0) {
        psw->grfFx = 8;
    } else {
        psw->grfFx = 0;
    }
    psw->HandleSpliceEvent(0x10, 0, 0, 0, 0);
    if (psw->grfFx & 1)
        return;
    STGNODE *pnode = &psw->anode[psw->istage];
    RunStgSwitchStage(psw, psw->anode - 1);
    RunStgSwitchStage(psw, pnode);
    if (psw->ploHit == 0 || !FIsBasicDerivedFrom(psw->ploHit, 0x38) || FIsBasicDerivedFrom(psw->ploHit, 0x3C) != 0)
        SpawnSwHitFx(&B_003DD490, 0, PosLoWorld(psw), psw->ploHit);
    if (pnode->fForward > 0) {
        psw->cframe++;
        if (psw->cframe >= pnode->fForward) {
            psw->cframe = 0;
            psw->istage++;
            if (psw->istage >= psw->cstage) {
                psw->PostMessage(0x10, psw);
                psw->HandleSpliceEvent(5, 0, 0, 0, 0);
                bevy_camera_follow_activity(B_002DEB30, 0x11, psw);
            }
        }
    }
    if (FStgSwitchInStageRange(psw) != 0) {
        pnode = &psw->anode[psw->istage];
        if (pnode->fForward <= 0) {
            for (int ipart = 0; ipart < psw->cpart; ipart++)
                psw->apart[ipart].active = 0;
        }
    }
}
}
