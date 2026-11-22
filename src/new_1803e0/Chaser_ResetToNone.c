/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct CHASER;

void Chaser_SetState(struct CHASER *pchaser, s32 state);              /* extern */
void func_0017F110(struct CHASER *pchaser);                            /* extern */

void Chaser_ResetToNone(struct CHASER *pchaser) {
    func_0017F110(pchaser);
    Chaser_SetState(pchaser, -1);
}
