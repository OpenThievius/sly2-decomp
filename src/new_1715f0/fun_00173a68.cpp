// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "ps2inline.h"
#include "stepguard.h"
#include "vu0inline.h"

struct POINT { u8 unknown_0x0[0x14]; int fBusy; };
struct SLOT { STEPGUARD *pactor; float tSpawn; u8 unknown_0x8[4]; POINT *ppoint; };
struct ROTATION { QW right; QW up; QW forward; };
struct CLOCK { float t; float dt; };
struct MESSAGE { void **ppactor; };
struct SPAWNER : LO { u8 unknown_0x50[0x8]; int cSlot; int cSlotMax; u8 unknown_0x60[0x10]; QW posLast; u8 unknown_0x80[0x28]; float tNext; int mode; };

extern SW B_003DD490;
extern "C" {
void UpdateLo(SPAWNER *);
QW PosSpawnerFocus(SPAWNER *);
void func_00173D18(SPAWNER *, QW);
void *PpoSwFocusBase(SW *);
ALERT *PalertFind(void *);
SLOT *func_00173E78(SPAWNER *, int);
POINT *func_00173F18(SPAWNER *, QW, QW *, ROTATION *, int *);
void func_00173928(SPAWNER *, SLOT *, int, int);
STEPGUARD *func_00174490(SPAWNER *, POINT *, QW *, ROTATION *, int);
void SetAloAlpha(STEPGUARD *, float);
void FadeAloIn(STEPGUARD *, float);
void func_00154038(int, int, int);
extern CLOCK g_2dded0;
extern float D_002BE5CC;
extern float D_002BE5D0;
extern float D_002BE5D4;
extern float D_002BE5D8;

void func_00173A68(SPAWNER *spawner)
{
    QW position[1];
    ROTATION rotation;
    int goal;
    UpdateLo(spawner);
    QW focus = PosSpawnerFocus(spawner);
    func_00173D18(spawner, focus);
    if (g_2dded0.t < spawner->tNext)
        return;
    spawner->tNext = g_2dded0.t + D_002BE5D0;
    if (spawner->cSlot == spawner->cSlotMax) {
        float distance = LaneX(SqrtX(SquaredLengthXy(VectorSub(focus, spawner->posLast))));
        int fNear = distance < D_002BE5D4;
        if (fNear)
            return;
    }
    ALERT *alert = 0;
    void *base = PpoSwFocusBase(&B_003DD490);
    if (base) {
        alert = PalertFind(base);
        if (alert) {
            if (alert->cguard == 0) {
                alert = 0;
            } else {
                switch (spawner->mode) {
                case 0:
                    return;
                case 1:
                    if (D_002BE5CC < g_2dded0.t - alert->tStart)
                        return;
                    break;
                case 2:
                case 3:
                    break;
                }
            }
        }
    }
    int handle = 0;
    if (alert && alert->cguard == 1)
        handle = (int)alert->apguard[0];
    SLOT *slot = func_00173E78(spawner, handle);
    if (!slot)
        return;
    POINT *point = func_00173F18(spawner, focus, position, &rotation, &goal);
    if (!point)
        return;
    spawner->posLast = focus;
    if (slot->pactor)
        func_00173928(spawner, slot, 0, 1);
    STEPGUARD *actor = func_00174490(spawner, point, position, &rotation, goal);
    if (!actor)
        return;
    SetAloAlpha(actor, 0.01f);
    FadeAloIn(actor, 0.5f);
    if (alert)
        func_00154038((int)actor->psensor, (int)alert->palo, 2);
    slot->pactor = actor;
    slot->tSpawn = g_2dded0.t;
    slot->ppoint = point;
    spawner->cSlot++;
    point->fBusy = 1;
    MESSAGE message;
    message.ppactor = (void **)&actor;
    spawner->tNext = g_2dded0.t + D_002BE5D8;
    spawner->HandleSpliceEvent(0x19, 0, 1, (int)&message, 0);
}
}
