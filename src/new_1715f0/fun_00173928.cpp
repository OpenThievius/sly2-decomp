#include "sly2.h"
#include "lo.h"
#include "clock.h"
/* A spawn point of the guard spawner: whether a guard holds it and when it is free again. */
struct SPAWNPOINT { u8 unknown_0x0[0x14]; s32 fBusy; f32 tReady; };
struct SLOT { LO *pactor; u8 unknown_0x4[4]; f32 tFree; SPAWNPOINT *ppoint; s32 kind; u8 unknown_0x14[0xC]; QW posRelease; };
/* The guard spawner (class not recovered): the slot count and the two delays func_00173928 adds to the clock. */
struct GUARDSPAWNER {
    u8 unknown_0x0[0x58];
    /* 0x58 */ s32 cSlot;
    u8 unknown_0x5C[0x44];
    /* 0xA0 */ f32 dtFree;    /* func_00173928: how long a released slot waits (kind 1) */
    /* 0xA4 */ f32 dtReady;   /* func_00173928: how long its spawn point waits (kind 1) */
};
extern "C" QW PosSpawnerFocus(void *);
extern "C" void func_00173928(GUARDSPAWNER *pspawner, SLOT *pslot, int kind, unsigned fKeepPoint)
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
