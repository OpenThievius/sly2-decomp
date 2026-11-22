// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

extern "C" {
void InitDprize(DPRIZE *);

// InitDprizeCoin
void func_001C6508(DPRIZECOIN *pcoin) {
    InitDprize(pcoin);
    pcoin->field_0x1D8 = 45.0f;
    pcoin->field_0x1DC = 65.0f;
    pcoin->field_0x1D0 = 250.0f;
    pcoin->field_0x1D4 = 150.0f;
    pcoin->field_0x1E0 = 0.5f;
    pcoin->field_0x1E4 = 0.25f;
    pcoin->field_0x1A0 = 0.25f;
    pcoin->waitMin = 5.0f;
    pcoin->waitMax = 5.0f;
}

}
