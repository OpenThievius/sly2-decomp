/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "carrypart.h"
#include "soview.h"

s32 IMax(s32 a, s32 b);
struct SOVIEW *func_001A5BF0(struct LO *plo);

s32 func_001CC9A8(struct CARRYPART *pcarry, struct SOVIEW *psoOther, s32 value) {
    struct SOVIEW *pso;

    if (pcarry->state == 1 && (pso = func_001A5BF0(pcarry->plo)) != 0) {
        if (pso->poxa != 0 && psoOther->poxa == pso->poxa)
            value = IMax(value, 3);
    }
    return value;
}
