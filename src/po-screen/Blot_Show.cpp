// SPDX-License-Identifier: GPL-3.0-or-later
#include "blot.h"

enum TIMERS { TIMERS_dummy };
extern "C" void SetBlotBlots(BLOT *, int);
extern "C" void SetTimerTimers__FP5TIMER6TIMERS(BLOT *, TIMERS);
extern "C" int FSpriteHasLabel(BLOT *, int, int);

void Blot_Show(BLOT *pblot, int labelStart) {
    if (pblot->blots == 0)
        SetBlotBlots(pblot, 1);
    SetTimerTimers__FP5TIMER6TIMERS(pblot, (TIMERS)2);
    pblot->labelVisible = labelStart;
    pblot->labelAppear = -1;
    pblot->labelDisappear = -1;
    if (labelStart != -1) {
        SetBlotBlots(pblot, 1);
        SetBlotBlots(pblot, 2);
    } else {
        pblot->labelVisible = 0x314;
        if (FSpriteHasLabel(pblot, pblot->asprite, 0x30F))
            pblot->labelAppear = 0x30F;
        if (FSpriteHasLabel(pblot, pblot->asprite, 0x310))
            pblot->labelVisible = 0x310;
        if (FSpriteHasLabel(pblot, pblot->asprite, 0x311))
            pblot->labelDisappear = 0x311;
        if (pblot->blots == 1) {
            pblot->Update();
        }
    }
}
