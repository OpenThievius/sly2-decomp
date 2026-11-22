// SPDX-License-Identifier: GPL-3.0-or-later
#include "rtalo.h"
extern "C" {
void func_00169198(void *pglobset, RTALO *prtalo);

void func_001BEE60(RTALO *prtalo) {
    SO **ppso;
    SO *pso;
    s32 ichild;

    if (prtalo->pwindow != 0) {
        ichild = 0;
        if (prtalo->count > 0) {
            ppso = prtalo->apso;
            do {
                pso = *ppso;
                ichild += 1;
                ppso += 1;
                func_00169198(&pso->field_0x80, prtalo);
            } while (ichild < prtalo->count);
        }
    }
}

}
