// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" {
int FIsGuardInSgs(STEPGUARD *, int);
QW ConvertAloPos(STEPGUARD *, int, QW);
int FFindSurfaceAlongUp(float, float, QW *, s64, void *);
void func_0020CFC0();
extern QW D_002C3E00[5];
extern float g_2c3e50;
extern float g_2c3e54;
}
int FGuardOffGround(FALLCHECK *pfallcheck)
{
    STEPGUARD *pguard = pfallcheck->pguard;
    if (pguard->psoSurface == 0) {
        if (pguard->modePath == -1) {
            if (pguard->field_0x4A0 != 0) {
                if (!FIsGuardInSgs(pguard, 0x13)) {
                    unsigned index = 0;
                    QW *ppos = D_002C3E00;
                    do {
                        QW pos = ConvertAloPos(pfallcheck->pguard, 0, *ppos);
                        if (FFindSurfaceAlongUp(g_2c3e50, g_2c3e54, &pos, 1, (void *)func_0020CFC0))
                            break;
                        index++;
                        ppos++;
                    } while (index < 5);
                    return (index < 5) ^ 1;
                }
            }
        }
    }
    return 0;
}
