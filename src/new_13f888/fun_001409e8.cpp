// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
#include "stepguard.h"
#include "hitfx.h"
extern "C" {
int bevy_player_p15_binoc_active(void *);
QW PosLoWorld(void *);
HITFX *PhitfxSpawn(void *, QW, void *);
int FIsGuardInSgs(void *, int);
int FHitFxSensorReaches(void *, void *);
void HitFx_Remove(void *);
}
struct HITFXSENSOR { u8 unknown_0x0[0x104]; HITFXSENSOR *pnext; };
extern "C" STEPGUARD *B_003E1444;
extern HITFXSENSOR *B_003E1468;
int func_001409E8(JT *jt)
{
    struct { float x, y, z, w; } unused;
    if (bevy_player_p15_binoc_active(jt))
        return 2;
    HITFX *handle = 0;
    if (jt->hitfxParms) {
        QW pos = PosLoWorld(jt);
        handle = PhitfxSpawn(jt->hitfxParms, pos, jt);
    }
    if (!handle)
        return 2;
    int state = 0;
    for (STEPGUARD *guard = B_003E1444; guard; guard = guard->pnext) {
        if (FIsGuardInSgs(guard, 0x1D) || FIsGuardInSgs(guard, 0xB)) {
            state = 2;
            break;
        }
        if (guard->Slot89(handle)) {
            state = 1;
            break;
        }
    }
    if (!state) {
        for (HITFXSENSOR *sensor = B_003E1468; sensor; sensor = sensor->pnext) {
            if (FHitFxSensorReaches(sensor, handle)) {
                state = 1;
                break;
            }
        }
    }
    HitFx_Remove(handle);
    return state;
}
