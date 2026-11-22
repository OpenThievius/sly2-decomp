/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "button.h"

void CSo_Clone();

void CloneButton(struct BUTTON *pbutton) {
    CSo_Clone();
    pbutton->btn.pbutton = pbutton;
}
