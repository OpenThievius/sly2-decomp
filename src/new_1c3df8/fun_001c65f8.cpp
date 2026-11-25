// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"
#include "rip.h"
#include "sw.h"

extern "C" {
float GRandInRange(float, float);
RIP *PripNewRipg(SW *, int, RIPG *);
QW PosLoWorld(DPRIZE *);
ROWS3 *PmatLoWorld(DPRIZE *);
int NewEmitter(int);
void SetEmitterUnpositioned(int, int);
void ShowCoinBlot(SW *);
void bevy_camera_follow_activity(void *, int, DPRIZE *);
void SetDprizeDprizes(DPRIZE *, int);
void func_001C67A0(DPRIZECOIN *, int);
extern SW B_003DD490;
extern void *D_002C0DA0[28];
extern char B_002DEB30;
}

// SetDprizeCoinDprizes (slot 76 of the coin)
void func_001C65F8(DPRIZECOIN *pcoin, int dprizes)
{
    if (pcoin->dprizes == dprizes) return;
    switch (dprizes) {
    case 0:
        pcoin->wait = GRandInRange(pcoin->waitMin, pcoin->waitMax);
        break;
    case 1: {
        RIPHUDSPOT *prip = (RIPHUDSPOT *)PripNewRipg(&B_003DD490, 9, 0);
        if (prip) {
            const RIPVTENTRY *pentry = &prip->pvtrip->slot1;
            prip->pdprizeTarget = pcoin;
            prip->pparam = D_002C0DA0;
            prip->field_0xF8 = 0;
            void *ptarget = (char *)prip + pentry->delta;
            QW pos = PosLoWorld(pcoin);
            pentry->fn(ptarget, pos, 1.0f, 0);
            prip->pdprize = pcoin;
            ROWS3 *pmat = PmatLoWorld(pcoin);
            prip->rowObject[0] = pmat->row[0];
            prip->rowObject[1] = pmat->row[1];
            prip->rowObject[2] = pmat->row[2];
        } else {
            func_001C67A0(pcoin, 0);
        }
        SetEmitterUnpositioned(NewEmitter(0x29), 0);
        MSGSINK *psink = (MSGSINK *)pcoin->aoidploB[1].plo;
        if (psink) {
            SINKMSG loc;
            int *msg = loc.aw;
            msg[0] = 1;
            msg[1] = (sptr)pcoin;
            psink->Notify(msg);
        }
        dprizes = 2;
        pcoin->HandleSpliceEvent(5, 0, 0, 0, 0);
        ShowCoinBlot(&B_003DD490);
        bevy_camera_follow_activity(&B_002DEB30, 0x12, pcoin);
        break;
    }
    }
    SetDprizeDprizes(pcoin, dprizes);
}
