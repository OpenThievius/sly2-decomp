// SPDX-License-Identifier: GPL-3.0-or-later
#include "hudlabel.h"
#include "sly2.h"
extern "C" void ClearHudLabel(HUDLABEL *, int);
extern "C" void SetHudLabelState(HUDLABEL *, int);
void ShowHudLabel(HUDLABEL *label, int id, float value) {
    if (id == -1) {
        ClearHudLabel(label, -1);
        return;
    }
    switch (label->state) {
    case 1:
        SetHudLabelState(label, -1);
    case 0:
    case 3:
        label->label = id;
        label->tHold = value;
        SetHudLabelState(label, 1);
        return;
    case 2:
        if (label->label == id) {
            label->tHold = value;
            return;
        }
    case 4:
        label->labelNext = id;
        label->tHoldNext = value;
    }
}
