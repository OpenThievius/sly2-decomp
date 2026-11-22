// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jtzap.h"

struct PMF { short delta; short index; void (*fn)(void *); };
extern "C" void WarpZapToSafePoint(JTZAP *);
extern "C" void SetJmpState(void *, int, int, int);

extern "C" void ZapContinue(JTZAP *zap)
{
    BYTES8 saved;
    saved = zap->continuation;
    memset(&zap->continuation, 0, 8);
    PMF *pmf = (PMF *)&saved;
    if (pmf->index != 0) {
        pmf->fn((char *)zap + pmf->delta);
        return;
    }
    if ((unsigned)(zap->state - 8) < 5) {
        JT *pjt = zap->pjt;
        pjt->Slot93();
        return;
    }
    if (zap->ptarget != 0 && (zap->ptarget->grfso & 0x200000000UL) != 0) {
        WarpZapToSafePoint(zap);
        return;
    }
    SetJmpState(zap->pjt->PvJmp(), 0xB, 0, 0);
}
