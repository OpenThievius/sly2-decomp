// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
#include "sw.h"
/* message 9 (an animation event): the animation instance it belongs to and the event label */
struct MSGANIMEVENT {
    /* 0x0 */ void *pinst;
    u8 unknown_0x4[0x4];
    /* 0x8 */ s32 label;
};
/* message 0xC (a hit): the hit's flags and strength */
struct MSGHIT {
    u8 unknown_0x0[0xC];
    /* 0xC */ s32 grfHit;
    /* 0x10 */ s32 cHit;
    u8 unknown_0x14[0x30];
    /* 0x44 */ s32 grfHitFx;
};
/* the effect object it spawns: slot 51 of its vtable takes the packet (the class is not known) */
/* what the effect's slot 0x198 takes: 0x40 bytes, cleared, kind 5 and a position */
struct HITFXPACKET {
    /* 0x0 */ s32 kind;
    u8 unknown_0x4[0x1C];
    /* 0x20 */ QW pos;
    u8 unknown_0x30[0x10];
};
/* an LO whose class declares slots 49 to 51 (51 takes the packet; it is not an SO, whose slot 51 is PxfFromRef) */
struct HITFXOBJ : LO {
    virtual void Slot49();
    virtual void Slot50();
    virtual void SetPacket(HITFXPACKET *packet);
};
extern "C" int D_002BE6D0[];
extern "C" int D_002BE6E8[];
extern "C" int GoalAnim_FHandleMessage(GOALANIM *, int, void *);
extern "C" void *func_00209518(void *);
extern "C" int FDoneAnimref(void *);
extern "C" void StopAnimref(void *);
extern "C" void StartAnimref(void *, void *, unsigned, float);
extern "C" float *PeaFindAsegLabel(void *, int);
extern "C" void SeekAsega(void *, int, float, float);
extern "C" void GoalAnimLeap_SetState(GOALGRAB *, int);
extern "C" HITFXOBJ *PloFindSwObject_thunk(SW *, int, int, int);
extern "C" void PhitfxSpawn(void *, QW, void *);
extern "C" QW PosLoWorld(void *);
extern SW B_003DD490;
// StartAnimref takes (void *, void *, unsigned, float) with the float last, as in GoalAnim_SetState; the draft put the float first, which
// moved the mtc1 and a lw before the other argument loads (score 4). No temporaries: the arguments are computed inline.
extern "C" int GoalAnimLeap_FHandleMessage(GOALGRAB *pgoal, int message, void *pargs)
{
    int hits, index, total;
    float seek;
    HITFXOBJ *effect;
    if (GoalAnim_FHandleMessage(pgoal, message, pargs))
        return 1;
    switch (message) {
    case 9:
        if (pgoal->panimref == 0)
            return 0;
        if (func_00209518(pgoal->panimref) != ((MSGANIMEVENT *)pargs)->pinst)
            return 0;
        if (((MSGANIMEVENT *)pargs)->label == 0x3D) {
            pgoal->chit = 0;
            goto zero;
        }
        return 0;
    case 0xC:
        break;
    default:
        return 0;
    }
    if (((MSGHIT *)pargs)->grfHit != 0x200000)
        return 0;
    if ((((MSGHIT *)pargs)->grfHitFx & 8) == 0)
        return 0;
    if (pgoal->phase == 0)
        return 0;
    if (FDoneAnimref(pgoal->panimref)) {
        StopAnimref(pgoal->panimref);
        StartAnimref(pgoal->panimref, pgoal->pstep, pgoal->panimref->grf | 1, 0.0f);
    }
    hits = pgoal->chit + 1;
    pgoal->chit = hits;
    seek = 0.0f;
    index = 4;
    if (hits < 4)
        index = hits;
    for (; index > 0; index--) {
        float *plabel = PeaFindAsegLabel(pgoal->panimref->pdata, D_002BE6D0[index]);
        if (plabel) {
            seek = *plabel;
            break;
        }
    }
    SeekAsega(pgoal->panimref->pinst, 0, seek, 1.0f);
    GoalAnimLeap_SetState(pgoal, 0);
    effect = PloFindSwObject_thunk(&B_003DD490, 5, D_002BE6E8[index], 0);
    if (effect) {
        HITFXPACKET packet;
        memset(&packet, 0, sizeof(packet));
        packet.kind = 5;
        packet.pos = PosLoWorld(pgoal->pstep);
        effect->SetPacket(&packet);
    }
    total = ((STEPGUARD *)pgoal->pstep)->field_0x33C + ((MSGHIT *)pargs)->cHit;
    ((STEPGUARD *)pgoal->pstep)->field_0x33C = total > 4 ? total : 5;
    PhitfxSpawn(B_003DD490.field_0x4028, PosLoWorld(pgoal->pstep), pgoal->pstep);
    return 1;
zero: /* the label is kept: without the goto the early returns merge differently (score 17) */
    return 0;
}
