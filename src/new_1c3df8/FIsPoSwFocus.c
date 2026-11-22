/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

struct PO *PpoSwFocus(struct SWVIEW *psw); /* extern */
extern struct SWVIEW B_003DD490;

s32 FIsPoSwFocus(struct PO *ppo) {
    return ppo == PpoSwFocus(&B_003DD490);
}
