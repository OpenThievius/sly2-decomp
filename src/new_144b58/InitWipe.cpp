// SPDX-License-Identifier: GPL-3.0-or-later
#include "wipe.h"
#include "sw.h"

extern "C" {
void InitSo(SO *pso);
void func_001A6CA8(SO *pso, int arg1);

void InitWipe(WIPE *pwipe) {
    InitSo(pwipe);
    pwipe->wipes = -1;
    func_001A6CA8(pwipe, 1);
    if (!(pwipe->grfSw & 1)) {
        pwipe->pgrfentry->grf |= 0x102;
    } else {
        pwipe->grfSw |= 0x102;
    }
}
}
