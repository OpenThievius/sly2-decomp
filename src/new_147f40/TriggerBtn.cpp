// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "button.h"
extern "C" void *NewEmitter(int);
extern "C" void SetEmitterUnpositioned(void *, BUTTON *);
extern "C" void RunBtnAsegs(BTN *, int);
void SetBtnButtons__FP3BTN7BUTTONS(BTN *, int);
void TriggerBtn(BTN *pbtn)
{
    pbtn->pbutton->HandleSpliceEvent(5, 0, 0, 0, 0);
    if (pbtn->field_0x9C == 0) {
        BUTTON *pbuttonEmit = pbtn->pbutton;
        void *pemitter = NewEmitter(2);
        SetEmitterUnpositioned(pemitter, pbuttonEmit);
    }
    RunBtnAsegs(pbtn, 0);
    if (pbtn->field_0xA4 == 0)
        SetBtnButtons__FP3BTN7BUTTONS(pbtn, 2);
    pbtn->pbutton->PostMessage(6, pbtn);
}
