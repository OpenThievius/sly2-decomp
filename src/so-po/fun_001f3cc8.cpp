// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"
#include "so.h"
struct RO { char b[0x30]; };
extern "C" void func_001A4478(void *, void *, void *);
extern "C" void RenderGlobset(void *, void *, float, float, void *);
extern "C" char B_003DD490;

void func_001F3CC8(SO *psoArg, void *pcmArg, void *proArg, float uAlpha, float uAlphaOther)
{
    void *pro = proArg;
    void *pcm = pcmArg;
    SO *pso = psoArg;
    struct { RO ro; char extra[0x10]; } local;
    if (pro == 0 && pso->field_0x134 != 0) {
        local.ro = *pso->field_0x134;
        pro = &local.ro;
        func_001A4478(&B_003DD490, pcm, &local.ro);
    }
    RenderGlobset(&pso->field_0x80, pcm, uAlpha, uAlphaOther, pro);
    for (LO *pchild = (LO *)pso->dlChild.head; pchild != pso->ploChildEnd; pchild = pchild->ploNext)
        pchild->Slot20(pcm, uAlpha, uAlphaOther, (RO *)pro);
}
