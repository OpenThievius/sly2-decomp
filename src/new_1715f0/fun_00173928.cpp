#include "sly2.h"
#include "lo.h"
#include "clock.h"
#include "stepguard.h"
#include "guardspawner.h"
extern "C" QW PosSpawnerFocus(void *);
extern "C" void func_00173928(GUARDSPAWNER *pspawner, GUARDSPAWNSLOT *pslot, int kind, unsigned fKeepPoint)
{
    pslot->kind = kind;
    switch (kind) {
    case 0:
        pslot->tFree = g_2dded0.t;
        pslot->pactor->Remove();
        if ((fKeepPoint ^ 1) & 1)
            pslot->ppoint->tReady = g_2dded0.t;
        break;
    case 1:
        pslot->tFree = g_2dded0.t + pspawner->dtFree;
        pslot->posRelease = PosSpawnerFocus(pspawner);
        if ((fKeepPoint ^ 1) & 1)
            pslot->ppoint->tReady = g_2dded0.t + pspawner->dtReady;
        break;
    }
    pslot->pactor = 0;
    pslot->ppoint->fBusy = 0;
    pslot->ppoint = 0;
    pspawner->cSlot--;
}
