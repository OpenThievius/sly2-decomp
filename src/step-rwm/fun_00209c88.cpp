/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "stepguard.h"
struct SLOT { short delta; short index; void (*fn)(void *, int, void *, QW, QW, QW); };
struct VT { char pad[0x290]; SLOT slot; };
struct VOBJ { char pad0[0xC]; VT *vt; };
extern "C" {
extern QW g_2a2da0;
void func_001F4FA8(void);
void GetPathPosFromS(void *, float, QW *, QW *);
QW PosLoWorld(void *);
QW *PmatLoWorld(void *);
void func_00209C88(STEPGUARD *guard)
{
    QW bufA;
    QW bufB;
    func_001F4FA8();
    switch (guard->modePath) {
    case 0: {
        GetPathPosFromS(guard->ptargetPath, guard->sPath, &bufA, &bufB);
        SLOT *slot = &((VOBJ *)guard)->vt->slot;
        slot->fn((char *)guard + slot->delta, 0x22, guard->ptargetPath, bufA, bufB, *guard->ppos);
        break;
    }
    case 1: {
        GetPathPosFromS(guard->ptargetPath, guard->sPath, &bufA, &bufB);
        SLOT *slot = &((VOBJ *)guard)->vt->slot;
        char *self = (char *)guard + slot->delta;
        QW posA = bufA;
        QW posB = bufB;
        slot->fn(self, 7, guard->ptargetPath, posA, posB, PosLoWorld(guard->prefPath));
        break;
    }
    case 2: {
        SLOT *slot = &((VOBJ *)guard)->vt->slot;
        char *self = (char *)guard + slot->delta;
        QW posA = PosLoWorld(guard->ptargetPath);
        QW posB = *PmatLoWorld(guard->ptargetPath);
        slot->fn(self, 7, guard->ptargetPath, posA, posB, PosLoWorld(guard->prefPath));
        break;
    }
    case 3: {
        SLOT *slot = &((VOBJ *)guard)->vt->slot;
        char *self = (char *)guard + slot->delta;
        QW posA = PosLoWorld(guard->ptargetPath);
        slot->fn(self, 7, guard->ptargetPath, posA, g_2a2da0, *guard->ppos);
        break;
    }
    }
}
}
