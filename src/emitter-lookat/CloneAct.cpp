// SPDX-License-Identifier: GPL-3.0-or-later
#include "lookat.h"
#include "sw.h"
extern "C" {
void CopyAb__FPvT0Ui(void *pvDest, void *pvSource, unsigned int cb);
extern SLOTHEAP B_003E123C; /* a slot heap (0x18 bytes, before B_003E1254): its slot size */

void CloneAct(LOOKAT *plookatDest, LOOKAT *plookatSource, ALO *palo, XF *pxf) {
    plookatDest->lookatk = plookatSource->lookatk;
    plookatDest->priority = plookatSource->priority;
    plookatDest->xfkind = plookatSource->xfkind;
    plookatDest->palo = palo;
    plookatDest->pxf = pxf;
    CopyAb__FPvT0Ui((char *)plookatDest + 0x1C, (char *)plookatSource + 0x1C, B_003E123C.cb - 0x1C);
}

}
