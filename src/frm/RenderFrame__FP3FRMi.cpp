// SPDX-License-Identifier: GPL-3.0-or-later
#include "frm.h"

extern "C" {
void BuildAllDrawEnvGifs();
int FlushSaaUnpacks();
void SendDmaSyncGsFinish__FP10sceDmaChanP2QW(int, QW *);
extern int g_2de594;
extern int g_2de598;

void RenderFrame__FP3FRMi(FRM *frm, int fSendGif) {
    FlushSaaUnpacks();
    BuildAllDrawEnvGifs();
    SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_2de594, frm->pqwVifSend);
    if (fSendGif != 0) {
        SendDmaSyncGsFinish__FP10sceDmaChanP2QW(g_2de598, frm->pqwGif);
    }
}
}
