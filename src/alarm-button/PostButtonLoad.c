/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "button.h"

void PostBtnLoad(struct BTN *);
void PostSoLoad();
void SetButtonButtons(struct BUTTON *, int);

void PostButtonLoad(struct BUTTON *pbutton) {
    PostSoLoad();
    PostBtnLoad(&pbutton->btn);
    SetButtonButtons(pbutton, 0);
}
