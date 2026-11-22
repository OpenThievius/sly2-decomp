// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
extern "C" {
s32 IdCurrentLevel(void);
extern s32 *B_003E1C44; /* per level, read as a byte by LoadLevelTableFromBrx; IEpisodeCurrent returns the current level's */
s32 IEpisodeCurrent(void) {
    s32 idLevel = IdCurrentLevel();
    if (idLevel == -1) {
        return -1;
    }
    return B_003E1C44[idLevel];
}
}
