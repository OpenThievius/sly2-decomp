// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"

extern "C" {
void AddGrfusr__Fi(int grfusr);
void IncrementSwBinocCount(SW *psw);
void IncrementSwShowCount(SW *psw);

void SetHandsOff(SW *psw, int grf) {
    int chandsOff = psw->chandsOff + 1;
    psw->chandsOff = chandsOff;
    if (chandsOff == 1) {
        AddGrfusr__Fi(2);
    }
    if (grf & 1) {
        IncrementSwShowCount(psw);
    }
    if (grf & 2) {
        IncrementSwBinocCount(psw);
    }
}
}
