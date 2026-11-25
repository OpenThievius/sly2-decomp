#include "sly2.h"
#include "act.h"
struct ALO;
extern "C" void InvalidateXfSegment(ALO *, XF *);
extern "C" void InsertXfAct(ALO *palo, XF *pxf, ACT *pact)
{
    ACT **ppactLink = &pxf->pactFirst;
    ACT *pactTopOld = pxf->pactFirst;
    for (ACT *pactCur = pactTopOld; pactCur && pactCur->priority > pact->priority; pactCur = pactCur->pactNext)
        ppactLink = &pactCur->pactNext;
    pact->pactNext = *ppactLink;
    *ppactLink = pact;
    if (pxf->pactFirst != pactTopOld) {
        InvalidateXfSegment(palo, pxf);
        if (pactTopOld) {
            ACTVT *vtOld = (ACTVT *)pactTopOld->vtable;
            vtOld->slot2.fn((char *)pactTopOld + vtOld->slot2.delta);
        }
        ACT *pactNew = pxf->pactFirst;
        ACTVT *vtNew = (ACTVT *)pactNew->vtable;
        vtNew->slot1.fn((char *)pactNew + vtNew->slot1.delta);
    } else {
        if (pactTopOld) {
            ACTVT *vtOld = (ACTVT *)pactTopOld->vtable;
            vtOld->slot3.fn((char *)pactTopOld + vtOld->slot3.delta);
        }
    }
}
