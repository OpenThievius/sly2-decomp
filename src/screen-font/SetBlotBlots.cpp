#include "sly2.h"
#include "sw.h"
#include "blot.h"
struct CLOCKS { u8 unknown_0x0[0x3C]; float dtScaled; };
extern SW B_003DD490;
extern CLOCKS g_2dded0;
extern int g_2dd318;
extern int g_2be538;
extern "C" {
void SetClockRate(void *, int, float);
void PrepareBlotMovie(BLOT *);
void ReleaseBlotMovie(BLOT *);
void StopBlotLabel(BLOT *);
void PlayBlotLabel(BLOT *, int);
void SetBlotBlots(BLOT *pblot, int state)
{
    if (pblot->blots == state)
        return;
    if (pblot->order >= 0x10) {
        if (pblot->blots < 2 && state >= 2)
            B_003DD490.cblotActive++;
        else if (state < 2 && pblot->blots >= 2)
            B_003DD490.cblotActive--;
    }
    if (pblot->fSlowsClock) {
        if (pblot->blots < 2 && state >= 2) {
            if (++g_2dd318 == 1)
                SetClockRate(&g_2dded0, 7, 0.0f);
        } else if (state < 2 && pblot->blots >= 2) {
            if (--g_2dd318 == 0)
                SetClockRate(&g_2dded0, 7, 1.0f);
        }
    }
    if (pblot->blots == 0)
        PrepareBlotMovie(pblot);
    pblot->blots = state;
    pblot->time = g_2dded0.dtScaled;
    pblot->tagState = g_2be538;
    switch (state) {
    case 0:
        ReleaseBlotMovie(pblot);
        break;
    case 1:
        StopBlotLabel(pblot);
        break;
    case 2:
        PlayBlotLabel(pblot, pblot->labelVisible);
        break;
    case 3:
        PlayBlotLabel(pblot, pblot->labelAppear);
        break;
    case 4:
        PlayBlotLabel(pblot, pblot->labelDisappear);
        break;
    }
}
}
