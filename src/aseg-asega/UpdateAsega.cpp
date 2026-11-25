// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"
#include "sly2.h"
extern float g_2ddf10;
extern float g_2dded4;
extern "C" {
void HandleAsegaEvents(ASEGA *);
int FAsegaGone(ASEGA *);
int FWrapAsegaTime(ASEGA *, float *, float *);
void RetractAsega(ASEGA *);
}
static inline unsigned GrfValue(ASEG *aseg)
{
    unsigned value = aseg->grfSw;
    if ((value ^ 1) & 1)
        return *(unsigned *)value;
    return value;
}
struct AsegaHold {
    ASEGA *pasega;
    AsegaHold(ASEGA *target) { pasega = target; pasega->OnAdd(); }
    ~AsegaHold() { pasega->Slot2(); }
};
extern "C" void UpdateAsega(ASEGA *asega)
{
    if (__builtin_fabsf(asega->svtLocal) < 0.0001f)
        return;
    AsegaHold hold(asega);
    unsigned grf = GrfValue(asega->paseg);
    if (grf & 0x100)
        asega->tLocal = asega->tLocal + asega->svtLocal * g_2ddf10;
    else
        asega->tLocal = asega->tLocal + asega->svtLocal * g_2dded4;
    HandleAsegaEvents(asega);
    if (FAsegaGone(asega))
        return;
    int wrapped = FWrapAsegaTime(asega, &asega->tLocal, &asega->svtLocal);
    if (wrapped) {
        if (asega->grfapl & 8)
            asega->iea = asega->svtLocal <= 0.0f ? asega->paseg->iea : 0;
    }
    if (wrapped) {
        asega->PostMessage(3, asega);
        if (FAsegaGone(asega))
            return;
    }
    HandleAsegaEvents(asega);
    if (FAsegaGone(asega))
        return;
    if (wrapped && (asega->grfapl & 0x38) == 0)
        RetractAsega(asega);
    for (PARTLINK *plink = asega->plink; plink != 0; plink = plink->pnext)
        plink->psink->Slot2(plink->nTarget, 0, asega->tLocal, asega->svtLocal);
}
