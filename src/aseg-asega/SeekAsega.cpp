// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
#include "alo.h"
#include "asega.h"
#include "xf.h"

extern "C" int FAsegaGone(ASEGA *);
extern "C" void FWrapAsegaTime(ASEGA *, float *, float *);
void UpdateAsegaIeaCur__FP5ASEGA(ASEGA *);
extern "C" int FActDrivesXf(ACTASEG *);
extern "C" void WakeXf(ALO *, XF *);
extern "C" void SnapAsega(ASEGA *, int);

extern "C" void SeekAsega(ASEGA *pasega, int seek, float dtLocal, float svtLocal)
{
    if (FAsegaGone(pasega))
        return;
    pasega->svt = svtLocal;
    pasega->svtLocal = svtLocal * pasega->svtMaster * pasega->factor;
    float tNew;
    switch (seek) {
    case 0: tNew = dtLocal; break;
    case 1: tNew = pasega->tLocal + dtLocal; break;
    case 2: tNew = pasega->paseg->tLength + dtLocal; break;
    }
    if (tNew != pasega->tLocal) {
        pasega->tLocal = tNew;
        FWrapAsegaTime(pasega, &pasega->tLocal, &pasega->svtLocal);
        UpdateAsegaIeaCur__FP5ASEGA(pasega);
        for (ACTASEG *pact = pasega->pactFirst; pact != 0; pact = pact->pactNext) {
            if (!FActDrivesXf(pact))
                continue;
            float tCurrent = *pact->act.pxf->ptMin;
            if (tCurrent < pact->act.pxf->tMin || pact->act.pxf->tMax < tCurrent) {
                ACTVT *vt = (ACTVT *)pact->act.vtable;
                vt->slot4.fn((char *)pact + vt->slot4.delta);
            }
            WakeXf(pact->act.palo, pact->act.pxf);
        }
        SnapAsega(pasega, 0);
    }
    pasega->tTarget = pasega->tLocal;
}
