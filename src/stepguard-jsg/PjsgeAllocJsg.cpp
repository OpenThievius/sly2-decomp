// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
/* local: jsg.h reads 0x50 as phase and 0x54 as an s32 ajsge; here they are the count and the record array of the queue PjsgeAllocJsg fills */
struct JSGE { int jsgek; int fAsync; u8 unknown_0x8[0x48]; };
struct JSG { u8 unknown_0x0[0x50]; int cjsge; JSGE *ajsge; int cjsgeMax; };
extern JSGE B_003DA740;
extern "C" JSGE *PjsgeAllocJsg(JSG *pjsg, int jsgek, int fAsync)
{
    int cjsge = pjsg->cjsge;
    int cjsgeMax = pjsg->cjsgeMax;
    if (cjsgeMax < 0)
        cjsgeMax = 0x200;
    if (cjsge >= cjsgeMax)
        return &B_003DA740;
    pjsg->cjsge = cjsge + 1;
    JSGE *pjsge = &pjsg->ajsge[cjsge];
    memset(pjsge, 0, 0x50);
    pjsge->jsgek = jsgek;
    pjsge->fAsync = fAsync;
    return pjsge;
}
