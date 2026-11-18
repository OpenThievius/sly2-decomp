/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
struct SLOT { short delta; short index; void (*fn)(void *, int, void *, QW, QW, QW); };
struct VT { char pad[0x290]; SLOT slot; };
struct GUARD { char pad0[0xC]; VT *vt; char pad1[0x218 - 0x10]; QW *pdir; char pad2[0xF80 - 0x21C]; int mode; void *target; float s; int pad3; void *from; };
extern "C" {
extern QW g_2a2da0;
void func_001F4FA8(void);
void GetPathPosFromS(void *, float, QW *, QW *);
QW PosLoWorld(void *);
QW *PmatLoWorld(void *);
void func_00209C88(GUARD *guard)
{
    QW bufA;
    QW bufB;
    func_001F4FA8();
    switch (guard->mode) {
    case 0: {
        GetPathPosFromS(guard->target, guard->s, &bufA, &bufB);
        SLOT *slot = &guard->vt->slot;
        slot->fn((char *)guard + slot->delta, 0x22, guard->target, bufA, bufB, *guard->pdir);
        break;
    }
    case 1: {
        GetPathPosFromS(guard->target, guard->s, &bufA, &bufB);
        SLOT *slot = &guard->vt->slot;
        char *self = (char *)guard + slot->delta;
        QW posA = bufA;
        QW posB = bufB;
        slot->fn(self, 7, guard->target, posA, posB, PosLoWorld(guard->from));
        break;
    }
    case 2: {
        SLOT *slot = &guard->vt->slot;
        char *self = (char *)guard + slot->delta;
        QW posA = PosLoWorld(guard->target);
        QW posB = *PmatLoWorld(guard->target);
        slot->fn(self, 7, guard->target, posA, posB, PosLoWorld(guard->from));
        break;
    }
    case 3: {
        SLOT *slot = &guard->vt->slot;
        char *self = (char *)guard + slot->delta;
        QW posA = PosLoWorld(guard->target);
        slot->fn(self, 7, guard->target, posA, g_2a2da0, *guard->pdir);
        break;
    }
    }
}
}
