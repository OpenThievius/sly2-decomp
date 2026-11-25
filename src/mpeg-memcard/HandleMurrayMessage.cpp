// SPDX-License-Identifier: GPL-3.0-or-later
#include "murray.h"
#include "sw.h"
/* The payload of messages 9 and 10 (an animation event): the handle that raised it, the previous and the new animation event id;
   as MSG9_188F20 of HandleSlyMessage. */
struct MSGANIM {
    void *psrc;
    s32 idPrevious;
    s32 id;
};
extern "C" {
void CarryThrow_Launch(void *);
void HandleJtMessage(JT *, s32, void *);
QW PosLoWorld(LO *);
void SetMurrayLiftState(MURRAY *, s32);
void SetMurrayState(MURRAY *, s32);
void SpawnSwHitFx(SW *, s32, QW, LO *);
void ThrowMurrayObject(MURRAY *);
void func_001B6DA8(MURRAY *, s32);
void func_001B7AE8(MURRAY *);
extern SW B_003DD490;
extern f32 RO_002C0990[];
extern f32 RO_002C099C;
void HandleMurrayMessage(MURRAY *pmurray, s32 msgid, MSGANIM *pmsg) {
    f32 timeLeft;
    HandleJtMessage(pmurray, msgid, pmsg);
    switch (msgid) {
    case 9:
        if ((pmsg->psrc == pmurray->field_0x1030) || (pmsg->psrc == pmurray->field_0x190C)) {
            switch (pmsg->id) {
            case 0x1A4:
                func_001B6DA8(pmurray, 1);
                break;
            case 0x1A5:
                SpawnSwHitFx(&B_003DD490, 0, PosLoWorld(pmurray), pmurray);
                break;
            case 0x1EB:
                switch (pmurray->state) {
                case 7:
                    ThrowMurrayObject(pmurray);
                    break;
                case 8:
                    func_001B7AE8(pmurray);
                    break;
                case 15:
                    CarryThrow_Launch(pmurray->PvCarry());
                    break;
                }
                break;
            case 0x1C6:
                pmurray->field_0x1448 = 1;
                break;
            case 0x1C8:
                if (pmurray->field_0x1450 == 0) {
                    SpawnSwHitFx(&B_003DD490, 0, PosLoWorld(pmurray), pmurray);
                    SetMurrayLiftState(pmurray, 1);
                }
                break;
            case 0x1C7:
                if (pmurray->field_0x1450 == 1) {
                    SetMurrayLiftState(pmurray, 2);
                }
                break;
            case 0x240:
                pmurray->field_0x1818 = 1;
                break;
            case 0x241:
                pmurray->field_0x181C = 1;
                break;
            case 0x242:
                pmurray->fCanChain = 1;
                break;
            }
        } else {
            return;
        }
        break;
    case 10:
        if ((pmsg->psrc == pmurray->field_0x1034) && (pmurray->state == 6)) {
            if (pmsg->id != pmsg->idPrevious) {
                switch (pmsg->id) {
                case 0x1D0:
                case 0x1CA:
                    SetMurrayState(pmurray, 0);
                    break;
                case 0x1CB: case 0x1CC: case 0x1CD: case 0x1CE: case 0x1CF:
                    f32 scale = RO_002C099C;
                    timeLeft = RO_002C0990[pmurray->iMashLevel];
                    pmurray->field_0x1528 = timeLeft;
                    pmurray->tMashLeft = timeLeft;
                    pmurray->cMashLeft = (s32) (scale * timeLeft);
                    break;
                }
            }
        }
        break;
    }
}
}
