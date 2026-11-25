// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" {
int FIsBasicDerivedFrom(void *, int);
u64 GrfsgsFromSgs(int);
SENSORENTRY *PentryFindSensorLo(void *, void *);
extern float g_2dded0;
extern float D_FLT_002C3DAC;
}
extern "C" int func_0020A298(STEPGUARD *pguard, void *plo, u64 grfsgs)
{
    unsigned int result;
    if (pguard->blocked == 0) {
        if (FIsBasicDerivedFrom(plo, 0x36)) {
            if (!FIsBasicDerivedFrom(pguard, 0x3A)) {
                if ((pguard->grfsgs & GrfsgsFromSgs(6)) == 0)
                    return 1;
            }
        }
        SENSORENTRY *pentry = PentryFindSensorLo(pguard->psensor, plo);
        if (pentry != 0 && pentry->state != 0 && (g_2dded0 - pentry->tFirst < D_FLT_002C3DAC) == 0) {
            if ((pguard->grfsgs & grfsgs) == 0)
                { result = 0; goto done; }
        }
        return 1;
    }
    { result = 0; goto done; }
done:
    return result;
}
