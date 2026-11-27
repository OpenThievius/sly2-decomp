// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "laser.h"
#include "xp.h"

/* a list of contacts (XP) that starts at 0x8: VEHICLEWHEEL::pxps has that offset (one reader, so a local view) */
struct CANDIDATELIST {
    u8 unknown_0x0[0x8];
    XP *pxpFirst;
};

XP *func_001D2DD0(void *self, CANDIDATELIST *list) {
    XP *candidate = list->pxpFirst;
    float bestScore = -3.4028235e38f;
    XP *best = 0;
    if (candidate != 0) {
        do {
            float score = candidate->gScale;
            if (bestScore < score) {
                bestScore = score;
                best = candidate;
            }
            candidate = candidate->pxpNext;
        } while (candidate != 0);
    }
    return best;
}
