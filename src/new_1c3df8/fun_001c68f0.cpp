// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"
#include "rip.h"
#include "sw.h"
#include "po.h"

extern "C" {
float GRandInRange(float, float);
RIP *PripNewRipg(SW *, int, RIPG *);
QW PosLoWorld(DPRIZE *);
ROWS3 *PmatLoWorld(DPRIZE *);
void SetDprizeDprizes(DPRIZE *, int);
void func_001C6AB0(DPRIZECHARM *, int);
PO *PpoSwFocusBase(SW *);
extern SW B_003DD490;
extern void *D_002C0E10[28];
}

// SetDprizeCharmDprizes (slot 76 of the charm): state 1 needs the player (slot 80), then heals it through slot 81
void func_001C68F0(DPRIZECHARM *pcharm, int dprizes)
{
    if (pcharm->dprizes == dprizes) return;
    switch (dprizes) {
    case 0:
        pcharm->wait = GRandInRange(pcharm->waitMin, pcharm->waitMax);
        break;
    case 1: {
        PO *ppo = PpoSwFocusBase(&B_003DD490);
        if (!ppo->FIsAvailable()) {
            dprizes = pcharm->dprizes;
            break;
        }
        RIPHUDSPOT *prip = (RIPHUDSPOT *)PripNewRipg(&B_003DD490, 9, 0);
        if (prip) {
            const RIPVTENTRY *pentry = &prip->pvtrip->slot1;
            prip->pdprizeTarget = pcharm;
            prip->pparam = D_002C0E10;
            prip->field_0xF8 = 0;
            void *ptarget = (char *)prip + pentry->delta;
            QW pos = PosLoWorld(pcharm);
            pentry->fn(ptarget, pos, 1.0f, 0);
            prip->pdprize = pcharm;
            ROWS3 *pmat = PmatLoWorld(pcharm);
            prip->rowObject[0] = pmat->row[0];
            prip->rowObject[1] = pmat->row[1];
            prip->rowObject[2] = pmat->row[2];
        } else {
            func_001C6AB0(pcharm, 0);
        }
        ppo->Slot81(pcharm->healMin, pcharm->healMax);
        MSGSINK *psink = (MSGSINK *)pcharm->aoidploB[1].plo;
        if (psink) {
            SINKMSG loc;
            int *msg = loc.aw;
            msg[0] = 1;
            msg[1] = (sptr)pcharm;
            const MSGSINKVT *vt = psink->vt;
            vt->fn((char *)psink + vt->delta, msg);
        }
        dprizes = 2;
        pcharm->HandleSpliceEvent(5, 0, 0, 0, 0);
        break;
    }
    }
    SetDprizeDprizes(pcharm, dprizes);
}
