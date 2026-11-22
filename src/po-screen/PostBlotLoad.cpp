// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "blot.h"

extern "C" void PostLoLoad(BLOT *);
extern "C" void *PloFindSwObject_thunk(SW *, int, int, void *);
extern "C" void func_001A6CA8(BLOT *, int);
extern "C" SW B_003DD490;

void PostBlotLoad(BLOT *blot) {
    PostLoLoad(blot);
    if (blot->field_0xBC != 0 && B_003DD490.pfont == 0)
        B_003DD490.pfont = PloFindSwObject_thunk(&B_003DD490, 0x405, 0x374, blot);
    int height = blot->height;
    blot->pblotSelf = blot;
    blot->field_0xA8 = -1;
    int quotient = (height << 9) / 0x280;
    float scaled = (float)blot->width * 0.45454547f;
    blot->field_0xA0 = 2048.0f - scaled * 0.5f;
    blot->field_0x9C = 2048.0f - (float)quotient * 0.5f;
    if (blot->field_0x6D != 0) {
        blot->Select(-1);
    }
    func_001A6CA8(blot, 1);
    if (!(blot->grfSw & 1))
        blot->pgrfentry->grf |= 0x102;
    else
        blot->grfSw |= 0x102;
}
