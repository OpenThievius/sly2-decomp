// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "pzo_hide.h"
extern "C" float SMaxCrv(CRV *);
static inline float GClamp(float value, float lower, float upper)
{
    if (value < lower)
        return lower;
    if (upper < value)
        return upper;
    return value;
}

// Retail computes the lerp as (1 - t) * field2C + t * field30 (the 1 - t product is the
// first operand of the add.s), and keeps the clamped value and the midpoint
// (field2C + field30) * 0.5 in the same register ($f3): the source reuses one local for
// both; a separate midpoint local gets its own register (score 14).
extern "C" void SwarmGroup_UpdateTargets(void *pswarm, SWARMGROUP *pgroup)
{
    float sCurve = SMaxCrv(pgroup->pcrv);
    float gapMax = (sCurve * 0.5f) / (float)pgroup->alive;
    float gap = pgroup->gap < gapMax ? pgroup->gap : gapMax;
    int index = 0;
    for (SWARMRIDER *prider = (SWARMRIDER *)pgroup->dl.head; prider; prider = (SWARMRIDER *)prider->dle.next) {
        int remaining = pgroup->alive - index - 1;
        float fraction = (pgroup->target - prider->field_0x34) / (prider->field_0x38 - prider->field_0x34);
        fraction = GClamp(fraction, 0.0f, 1.0f);
        float value = (1.0f - fraction) * prider->field_0x2C + fraction * prider->field_0x30;
        float lower = ((float)index + (float)index + 1.0f) * gap;
        float upper = sCurve - (((float)remaining + (float)remaining) + 1.0f) * gap;
        value = GClamp(value, lower, upper);
        prider->sGoal = value;
        value = (prider->field_0x2C + prider->field_0x30) * 0.5f;
        prider->priority = -fabsf(value - pgroup->target);
        index++;
    }
}
