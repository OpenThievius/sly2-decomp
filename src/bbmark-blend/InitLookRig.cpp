#include "sly2.h"
#include "lookrig.h"
void EnsureAsegBlendDynamic(void *, int, int, void *, int, int *, int *, void *);
void InitLookRig(float gUnused, float zStart, LOOKRIG *plookrig, JT *pjt, QW vecLook)
{
    plookrig->pjt = pjt;
    plookrig->vecTarget = vecLook;
    plookrig->rMin = zStart;
    plookrig->state = -1;
    for (unsigned irec = 0; irec < 6; irec++) {
        LOOKRIGENTRY *pentry = &plookrig->aentry[irec];
        EnsureAsegBlendDynamic(plookrig->pjt, 0xC, 2, pentry, 0, 0, 0, &pentry->paseg);
    }
}
