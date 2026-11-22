// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "guard.h"
#include "stepguard.h"
struct DIRANIM;
struct DIRANIMS;
extern "C" {
void ApplyAseg(void *paseg, void *paloRoot, float tLocal, float svtLocal, int grfapl, void **ppinst);
void PsmaApplySmInternal_thunk(void *psma, void *paloRoot, int tLocal, int grfapl, void **ppinst);
void StartJumpAnim(JUMPANIM *pjumpanim, STEP *pso, int field_0x3C, JUMPER *pjumper);
void StartDirAnim(DIRANIMS *pdiranims, void *palo, int grfapl, DIRANIM *pdiranim);
}

/* slot 1 of the playing instance (BASIC's, called through its delta) */
static inline void Go(void *pinst) { ((BASIC *)pinst)->OnAdd(); }

void StartAnimref(float gStart, ANIMREF *ref, STEPGUARD *owner, int grf)
{
    switch (ref->kind) {
    case 0:
        ApplyAseg(ref->pdata, owner, gStart, 1.0f, grf, &ref->pinst);
        Go(ref->pinst);
        break;
    case 1:
        PsmaApplySmInternal_thunk(ref->pdata, owner, -1, grf, &ref->pinst);
        Go(ref->pinst);
        break;
    case 2:
        ref->pinst = &owner->jumper;
        StartJumpAnim((JUMPANIM *)ref->pdata, owner, grf, &owner->jumper);
        Go(ref->pinst);
        break;
    case 3:
        ref->pinst = owner->diranim;
        StartDirAnim((DIRANIMS *)ref->pdata, owner, grf, (DIRANIM *)owner->diranim);
        Go(ref->pinst);
        break;
    case -1:
        return;
    }
}
