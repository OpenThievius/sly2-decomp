// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
extern "C" {
s32 IdCurrentLevel(void);
extern s32 *B_003E1C48; /* per level, read as a byte by LoadLevelTableFromBrx; func_00210A98 returns the current level's */
s32 func_00210A98(void) {
    s32 idLevel = IdCurrentLevel();
    return idLevel == -1 ? -1 : B_003E1C48[idLevel];
}
}
