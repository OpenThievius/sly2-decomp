#include "blot.h"
struct CLK { u8 unknown_0x0[0x3C]; float t; };
extern "C" {
void UpdateLo(BLOT *);
int FBlotLabelPlaying(BLOT *, int);
void SetTimerTimers__FP5TIMER6TIMERS(BLOT *, int);
void SetBlotBlots(BLOT *, int);
void UpdateRootSprite(void *, float);
extern CLK g_2dded0;
extern float g_2ddf10;
}
void UpdateBlotMovie(BLOT *blot)
{
    UpdateLo(blot);
    int blots = blot->blots;
    if (blots == 1) {
        if (blot->field_0x64 == 2)
            blots = (blot->labelAppear == -1) ? 2 : 3;
    } else if (blot->tLast != g_2dded0.t) {
        switch (blots) {
        case 2:
            if (!FBlotLabelPlaying(blot, blot->cur))
                SetTimerTimers__FP5TIMER6TIMERS(blot, 1);
            {
                float visible = *(float *)&blot->field_0x8C;
                if (0.0f < visible && visible < g_2dded0.t - blot->time)
                    SetTimerTimers__FP5TIMER6TIMERS(blot, 1);
            }
            if (blot->field_0x64 == 1)
                blots = (blot->labelDisappear == -1) ? 1 : 4;
            break;
        case 3:
            if (!FBlotLabelPlaying(blot, blot->labelAppear)) {
                switch (blot->field_0x64) {
                case 1:
                    blots = (blot->labelDisappear == -1) ? 1 : 4;
                    break;
                case 2:
                    blots = 2;
                    break;
                }
            }
            break;
        case 4:
            if (!FBlotLabelPlaying(blot, blot->labelDisappear)) {
                switch (blot->field_0x64) {
                case 1:
                    blots = 1;
                    break;
                case 2:
                    blots = (blot->labelAppear == -1) ? 2 : 3;
                    break;
                }
            }
            break;
        }
    }
    SetBlotBlots(blot, blots);
    if (blot->cur != -1) {
        blot->labelTime = blot->labelTime + g_2ddf10;
        UpdateRootSprite((void *)blot->asprite, g_2ddf10);
    }
}
