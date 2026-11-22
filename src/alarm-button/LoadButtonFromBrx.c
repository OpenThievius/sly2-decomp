/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "button.h"

void LoadBtn(struct BTN *, struct BUTTON *);
void CSo_LoadFromBrx();

void LoadButtonFromBrx(struct BUTTON *pbutton) {
    CSo_LoadFromBrx();
    LoadBtn(&pbutton->btn, pbutton);
}
