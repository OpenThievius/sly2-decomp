#include "blot.h"
extern "C" {
void SetBlotBlots(BLOT *, s32);
s32 SetTimerTimers__FP5TIMER6TIMERS(BLOT *, s32);
void Blot_Hide(BLOT *arg0) {
    SetTimerTimers__FP5TIMER6TIMERS(arg0, 1);
    if (arg0->labelDisappear == -1) {
        SetBlotBlots(arg0, 1);
    }
}
}
