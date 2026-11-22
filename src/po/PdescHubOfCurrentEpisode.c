/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

s32 IEpisodeCurrent(void);
void *PdescFromEpisode(s32);

void PdescHubOfCurrentEpisode(void) {
    PdescFromEpisode(IEpisodeCurrent());
}
