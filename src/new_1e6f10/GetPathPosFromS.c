// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"

struct CRV;
f32 UFromCrvS(struct CRV *pcrv, f32 s);
void EvaluateCrvFromU(struct CRV *pcrv, f32 u, QW *ppos, QW *pnormTangent);

void GetPathPosFromS(struct CRV *pcrv, QW *ppos, QW *pnormTangent, f32 s) {
    EvaluateCrvFromU(pcrv, UFromCrvS(pcrv, s), ppos, pnormTangent);
}
