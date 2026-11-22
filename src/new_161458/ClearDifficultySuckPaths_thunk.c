/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct DIFFICULTY;

void func_00154A80(struct DIFFICULTY *pdifficulty);
extern struct DIFFICULTY B_002DE578;

void ClearDifficultySuckPaths_thunk(void) {
    func_00154A80(&B_002DE578);
}
