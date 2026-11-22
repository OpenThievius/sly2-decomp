// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void func_0017F6B0(GRAB *);
extern "C" void func_001815E8(GRAB *, int);
extern "C" void TriggerRsmg(void *, int, RSMG *, void *, int);
extern SW B_003DD490;

void func_00181598(GRAB *grab) {
    func_0017F6B0(grab);
    func_001815E8(grab, 0);
    TriggerRsmg(&B_003DD490, grab->crsmg, grab->arsmg, grab, 0);
}
