// SPDX-License-Identifier: GPL-3.0-or-later
#include "frm.h"
struct GIFS { u8 unknown_0x0[0x30]; };
struct VIFS { u8 unknown_0x0[0x30]; };
extern "C" {
void FinalizeFrameVifs__FP4VIFSPiPP2QW(VIFS *, int *, QW **);
void FinalizeFrameGifs__FP4GIFSPiPP2QW(GIFS *, int *, QW **);
void ClearDl__FP2DL(DL *);
int SignalSema(int);
extern VIFS g_2dea28;
extern GIFS B_002DEA00;
extern DL B_002DEAF0;
extern DL B_002DEB00;
extern FRM *g_2dea4c;
extern int g_2deb18;
}
void CloseFrame()
{
    FinalizeFrameVifs__FP4VIFSPiPP2QW(&g_2dea28, &g_2dea4c->cqwVif, &g_2dea4c->pqwVif);
    FinalizeFrameGifs__FP4GIFSPiPP2QW(&B_002DEA00, &g_2dea4c->cqwGif, &g_2dea4c->pqwGif);
    FRM *frm = g_2dea4c;
    frm->cqwVifSend = ((int)frm->pqwVif + frm->cqwVif * 16 - (int)frm->pqwVifSend) >> 4;
    frm->dlBlipg = B_002DEAF0;
    ClearDl__FP2DL(&B_002DEAF0);
    g_2dea4c->dlBlip = B_002DEB00;
    ClearDl__FP2DL(&B_002DEB00);
    g_2dea4c = 0;
    SignalSema(g_2deb18);
}
