/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

struct PO *PpoSwFocusBase(struct SWVIEW *psw); /* extern */
extern struct SWVIEW B_003DD490;

s32 FIsPoSwFocusBase(struct PO *ppo) {
    return ppo == PpoSwFocusBase(&B_003DD490);
}
