#include "jtzap.h"
extern "C" int FAsegaGone(void *);
extern "C" void ZapContinue(JTZAP *);
extern "C" void UpdateZap(JTZAP *zap)
{
    int state;
    do {
        state = zap->state;
        if (FAsegaGone(zap->pjt->field_0x1030))
            ZapContinue(zap);
    } while (zap->state != -1 && zap->state != state);
}
