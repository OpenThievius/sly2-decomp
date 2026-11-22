/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

struct CHASER;
void func_0017F6B0(struct CHASER *);
void Chaser_SetState(struct CHASER *, s32);

void Chaser_Reset(struct CHASER *chaser) {
    func_0017F6B0(chaser);
    Chaser_SetState(chaser, 0);
}
