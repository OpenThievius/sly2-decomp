// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
extern "C" void PrimeSlotheap(SLOTHEAP *);
extern "C" void func_0020E338(SW *);
extern "C" void func_0020E2B0(SW *);
extern "C" void ClearSwRootFrameFlag(SW *);
extern "C" void InitCloneSets(SW *);
extern "C" void InitSwHudBlots(SW *);
extern "C" void InitSwHitFxParms(SW *);
extern "C" void func_001A3260(SW *);
extern "C" void func_001C10C8(SW *);
extern "C" void func_00210940(SW *);
extern "C" void FindTargetIndicatorTemplate(SW *);
extern "C" void ShutdownSplice__Fv(void *);
extern "C" void UpdateSwCallbacks(SW *);
extern "C" void BuildPzgraphAdjacency(PZGRAPH *);
extern "C" void func_0014D470(void *);
extern "C" void bevy_camera_follow_activity(void *, int, int);
extern "C" char B_003D9E70[], B_002DDF40[], B_002DEB30[];
void func_0020E740(SW *sw)
{
    PrimeSlotheap(&sw->slotheapRipg);
    PrimeSlotheap(&sw->slotheapRip);
    PrimeSlotheap(&sw->slotheapBlipg);
    PrimeSlotheap(&sw->slotheapBlip);
    func_0020E338(sw);
    func_0020E2B0(sw);
    ClearSwRootFrameFlag(sw);
    InitCloneSets(sw);
    InitSwHudBlots(sw);
    InitSwHitFxParms(sw);
    func_001A3260(sw);
    func_001C10C8(sw);
    func_00210940(sw);
    FindTargetIndicatorTemplate(sw);
    ShutdownSplice__Fv(B_003D9E70);
    for (;;) {
        UpdateSwCallbacks(sw);
        LO **end = sw->pploPostLoadEnd;
        LO **begin = sw->pploPostLoadBegin;
        if (end == begin)
            break;
        LO **current = begin;
        if (current < end) {
            do {
                LO *plo = *current++;
                plo->PostLoad();
            } while (current < sw->pploPostLoadEnd);
        }
        sw->pploPostLoadEnd = sw->pploPostLoadBegin;
    }
    sw->pploPostLoadEnd = 0;
    sw->pploPostLoadBegin = 0;
    sw->aoptset = 0;
    sw->adcb = 0;
    BuildPzgraphAdjacency(sw->ppzgraph);
    func_0014D470(B_002DDF40);
    bevy_camera_follow_activity(B_002DEB30, 4, 0);
}
