// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "joy.h"

extern "C" {
void DecrementSwBinocCount(SW *psw);
void DecrementSwShowCount(SW *psw);
void RemoveGrfusr__Fi(int grfusr);
void func_00187E08(JOY *pjoy, int grfbtn);
extern JOY B_002DFC00;

void ClearHandsOff(SW *psw, int grf) {
    int chandsOff = psw->chandsOff - 1;
    psw->chandsOff = chandsOff;
    if (chandsOff == 0) {
        RemoveGrfusr__Fi(2);
        func_00187E08(&B_002DFC00, 8);
    }
    if (grf & 1) {
        DecrementSwShowCount(psw);
    }
    if (grf & 2) {
        DecrementSwBinocCount(psw);
    }
}
}
