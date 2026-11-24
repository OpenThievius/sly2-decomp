// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "blot.h"
extern "C" {
void HideCountdownBlot(SW *arg0) {
    BLOT *obj = (BLOT *)arg0->ahudblot[3].plo;

    if (obj != 0) {
        obj->Hide();
        arg0->tEmit = 0.0f;
        return;
    }
    arg0->tEmit = 0.0f;
}

}
