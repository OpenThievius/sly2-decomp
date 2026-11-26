// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "laser.h"

/* a list of contacts (MQ) that starts at 0x8: VEHICLEWHEEL::pxps has that offset (one reader, so a local view) */
struct CANDIDATELIST {
    u8 unknown_0x0[0x8];
    MQ *pmqFirst;
};

MQ *func_001D2DD0(void *self, CANDIDATELIST *list) {
    MQ *candidate = list->pmqFirst;
    float bestScore = -3.4028235e38f;
    MQ *best = 0;
    if (candidate != 0) {
        do {
            float score = candidate->gScale;
            if (bestScore < score) {
                bestScore = score;
                best = candidate;
            }
            candidate = candidate->pmqNext;
        } while (candidate != 0);
    }
    return best;
}
