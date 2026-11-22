// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "guard.h"
#include "so.h"
#include "xf.h"
struct ASEG;
extern "C" {
void PostLoLoad(LO *);
int FIsBasicDerivedFrom(void *, int);
void BindAnimref(ANIMREF *, STEPGUARD *);
XF *func_001F4C58(STEPGUARD *, int, int);
float *PeaFindAsegLabel(void *, int);
void PredictAsegEffect(float, void *, void *, void *, void *, float, void *, int);
}
void PostGuardAimLoad(AIMSTATE *paim)
{
    PostLoLoad(paim);
    SO *pguard = paim->psoParent;
    while (pguard != 0 && !FIsBasicDerivedFrom(pguard, 0x38))
        pguard = pguard->psoParent;
    paim->pguard = (STEPGUARD *)pguard;
    ANIMREF *panimref;
    panimref = &paim->animref;
    BindAnimref(panimref, paim->pguard);
    if (paim->oid != 0x2CC)
        paim->panimref = panimref;
    if (paim->oidA != -1) {
        QW out[4];
        paim->pxfA = func_001F4C58(paim->pguard, paim->oidA, 6);
        paim->pxfB = func_001F4C58(paim->pguard, paim->oidB, 6);
        void *paseg = paim->animref.pdata;
        PredictAsegEffect(*PeaFindAsegLabel(paseg, paim->oidLabel), paseg, paim->pguard, paim->pxfB, paim->pxfA->pxfParent, 1.0f, out, 0);
        paim->vecRest = out[3];
    }
}
