// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

/* a linked list of scored candidates (what owns it is not known): the entry keeps its score at 0x90 and the next entry at 0xAC */
struct CANDIDATE {
    u8 unknown_0x0[0x90];
    f32 score;
    u8 unknown_0x94[0x18];
    CANDIDATE *pcandidateNext;
};
struct CANDIDATELIST {
    u8 unknown_0x0[0x8];
    CANDIDATE *pcandidateFirst;
};

CANDIDATE *func_001D2DD0(void *self, CANDIDATELIST *list) {
    CANDIDATE *candidate = list->pcandidateFirst;
    float bestScore = -3.4028235e38f;
    CANDIDATE *best = 0;
    if (candidate != 0) {
        do {
            float score = candidate->score;
            if (bestScore < score) {
                bestScore = score;
                best = candidate;
            }
            candidate = candidate->pcandidateNext;
        } while (candidate != 0);
    }
    return best;
}
