// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
s32 func_001EEFA0(GOALANIM *goal);

s32 func_00174EA0(GOALANIM *goal) {
    s32 result;
    s32 phase;
    s32 answer;
    ANIMREF *panimref;

    panimref = goal->panimref;
    if (panimref->kind == 2) {
        phase = ((JUMPER *)panimref->pinst)->state;
        answer = 7;
        if (phase != 0) {
            if ((phase >= 0)) {
                if ((phase < 5)) {
                    answer = 1;
                    if (phase >= 3) {
                        return 7;
                    }
                    { result = answer; goto done; }
                }
            }
            { result = 1; goto done; }
        }
        return answer;
    }
    answer = func_001EEFA0(goal);
    { result = answer; goto done; }
done:
    return result;
}

}
