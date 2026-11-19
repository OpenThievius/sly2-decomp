// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "ps2inline.h"
#include "vu0inline.h"

struct POINT { char pad[0x14]; int fBusy; };
struct VT { char pad[0x18]; short delta; short index; void (*fn)(void *, int, int, int, void *, int); };
struct ACTOR { char pad[0xF64]; int handle; };
struct SLOT { ACTOR *pactor; float tSpawn; char pad8[4]; POINT *ppoint; };
struct ALERT { float tSeen; char pad4[0xC - 4]; int handle; char pad10[0x28 - 0x10]; int kind; int target; };
struct ROTATION { QW right; QW up; QW forward; };
struct CLOCK { float t; float dt; };
struct MESSAGE { void **ppactor; };
struct SPAWNER { char pad[0xC]; VT *vptr; char pad10[0x58 - 0x10]; int cSlot; int cSlotMax; char pad60[0x70 - 0x60]; QW posLast; char pad80[0xA8 - 0x80]; float tNext; int mode; };

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
ACTOR *func_00174490(SPAWNER *, POINT *, QW *, ROTATION *, int);
void SetAloAlpha(ACTOR *, float);
void FadeAloIn(ACTOR *, float);
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
            if (alert->kind == 0) {
                alert = 0;
            } else {
                switch (spawner->mode) {
                case 0:
                    return;
                case 1:
                    if (D_002BE5CC < g_2dded0.t - alert->tSeen)
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
    if (alert && alert->kind == 1)
        handle = alert->target;
    SLOT *slot = func_00173E78(spawner, handle);
    if (!slot)
        return;
    POINT *point = func_00173F18(spawner, focus, position, &rotation, &goal);
    if (!point)
        return;
    spawner->posLast = focus;
    if (slot->pactor)
        func_00173928(spawner, slot, 0, 1);
    ACTOR *actor = func_00174490(spawner, point, position, &rotation, goal);
    if (!actor)
        return;
    SetAloAlpha(actor, 0.01f);
    FadeAloIn(actor, 0.5f);
    if (alert)
        func_00154038(actor->handle, alert->handle, 2);
    slot->pactor = actor;
    slot->tSpawn = g_2dded0.t;
    slot->ppoint = point;
    spawner->cSlot++;
    point->fBusy = 1;
    MESSAGE message;
    message.ppactor = (void **)&actor;
    spawner->tNext = g_2dded0.t + D_002BE5D8;
    spawner->vptr->fn((char *)spawner + spawner->vptr->delta, 0x19, 0, 1, &message, 0);
}
}
