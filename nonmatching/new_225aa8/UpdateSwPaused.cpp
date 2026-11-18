// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
extern "C" void UpdateAsega(void *);

void UpdateSwPaused(SW *psw)
{
    DLI iterator;
    int index;
    index = 0;
    psw->pigrfentryRunning = &index;
    for (index = 0; index < psw->cgrfentry; index++) {
        GRFENTRY *pgrfentry = &psw->agrfentry[index];
        if ((pgrfentry->grf & 0x102) == 0x102)
            pgrfentry->plo->Update();
    }
    psw->pigrfentryRunning = 0;
    PushDli(&iterator, &psw->dlAsega);
    LO *plo = (LO *)psw->dlAsega.head;
    iterator.m_ppv = (void **)((char *)plo + iterator.m_ibDle);
    while (plo != 0) {
        u32 grf = ((LO *)plo->proot)->grfSw;
        if (((grf ^ 1) & 1) != 0)
            grf = *(u32 *)grf;
        if (grf & 0x100)
            UpdateAsega(plo);
        plo = (LO *)PvStep(&iterator);
    }
    psw->pigrfentryRunning = &index;
    for (index = 0; index < psw->cgrfentry; index++) {
        GRFENTRY *pgrfentry = &psw->agrfentry[index];
        if ((pgrfentry->grf & 0x124) == 0x104)
            pgrfentry->plo->ProjectTransform();
    }
    psw->pigrfentryRunning = 0;
    PopDli(&iterator);
}
