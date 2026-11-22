// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct ENTRY { char pad[4]; int state; char pad2[4]; float t; };
#include "stepguard.h"
extern "C" {
int FIsBasicDerivedFrom(void *, int);
unsigned long GrfsgsFromSgs(int);
ENTRY *PentryFindSensorLo(void *, void *);
extern float g_2dded0;
extern float D_FLT_002C3DAC;
}
extern "C" int func_0020A298(STEPGUARD *pguard, void *plo, unsigned long grfsgs)
{
    unsigned int result;
    if (pguard->blocked == 0) {
        if (FIsBasicDerivedFrom(plo, 0x36)) {
            if (!FIsBasicDerivedFrom(pguard, 0x3A)) {
                if ((pguard->grfsgs & GrfsgsFromSgs(6)) == 0)
                    return 1;
            }
        }
        ENTRY * pentry;
        pentry = PentryFindSensorLo(pguard->psensor, plo);
        if (pentry != 0 && pentry->state != 0 && (g_2dded0 - pentry->t < D_FLT_002C3DAC) == 0) {
            if ((pguard->grfsgs & grfsgs) == 0)
                { result = 0; goto done; }
        }
        return 1;
    }
    { result = 0; goto done; }
done:
    return result;
}
