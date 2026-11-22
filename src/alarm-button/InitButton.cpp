// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "button.h"

extern "C" {
void InitBtn(BTN *);
void InitSo();

void InitButton(BUTTON *pbutton)
{
    InitSo();
    InitBtn(&pbutton->btn);
    if ((pbutton->grfSw ^ 1) & 1) {
        pbutton->pgrfentry->grf |= 2;
        return;
    }
    pbutton->grfSw |= 2;
}
}
