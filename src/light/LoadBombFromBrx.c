/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct BOMB;
void CSo_Clone(struct BOMB *bomb);
void InferExpl(struct BOMB *bomb, struct BOMB *owner);

void LoadBombFromBrx(struct BOMB *bomb) {
    CSo_Clone(bomb);
    InferExpl(bomb, bomb);
}
