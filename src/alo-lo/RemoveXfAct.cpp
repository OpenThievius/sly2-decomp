#include "act.h"
struct ALO;
void InvalidateXfSegment(ALO *, XF *);
static inline void CallSlot1(ACT *pact) { ACTVT *vt = (ACTVT *)pact->vtable; vt->slot1.fn((char *)pact + vt->slot1.delta); }
static inline void CallSlot2(ACT *pact) { ACTVT *vt = (ACTVT *)pact->vtable; vt->slot2.fn((char *)pact + vt->slot2.delta); }
static inline void CallSlot3(ACT *pact) { ACTVT *vt = (ACTVT *)pact->vtable; vt->slot3.fn((char *)pact + vt->slot3.delta); }

extern "C" void RemoveXfAct(ALO *palo, XF *pxf, ACT *pact)
{
    ACT *pactTopOld = pxf->pactFirst;
    ACT **ppactLink = &pxf->pactFirst;
    for (ACT *pactCur = pactTopOld; pactCur != 0; pactCur = pactCur->pactNext) {
        if (pactCur == pact) {
            *ppactLink = pactCur->pactNext;
            if (pxf->pactFirst != pactTopOld) {
                InvalidateXfSegment(palo, pxf);
                CallSlot2(pactTopOld);
                if (pxf->pactFirst != 0)
                    CallSlot1(pxf->pactFirst);
            } else if (pactTopOld != 0) {
                CallSlot3(pactTopOld);
            }
            return;
        }
        ppactLink = &pactCur->pactNext;
    }
}
