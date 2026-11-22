/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

struct PO *PpoSwFocus(struct SWVIEW *psw) {
    struct PO *ppo;

    ppo = psw->ppoFocusOverride;
    if (ppo == 0) {
        ppo = psw->ppoFocusBase;
    }
    return ppo;
}
