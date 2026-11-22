// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
struct RIGOBJ { char pad[0x16C]; void *psma; };
struct CLOCK { float t; float dt; };
extern "C" CLOCK g_2dded0;
extern "C" int D_002C3738[];
extern "C" void SetSmaGoalIfReachable(void *, int);

void func_001F17F8(STEPGUARD *pguard, int state)
{
    if (state == pguard->state)
        return;
    pguard->state = state;
    pguard->tState = g_2dded0.t;
    switch (state) {
    case -1:
    case 0:
        if (pguard->field_0x3F4)
            pguard->field_0x3F4->Remove();
        if (pguard->field_0x3F8)
            pguard->field_0x3F8->Remove();
        break;
    case 1:
    case 2:
        if (pguard->field_0x3F4)
            pguard->field_0x3F4->Add();
        if (pguard->field_0x3F8)
            pguard->field_0x3F8->Add();
        break;
    }
    void *psma = pguard->prig->psma;
    if (psma)
        SetSmaGoalIfReachable(psma, D_002C3738[pguard->state + 1]);
}
