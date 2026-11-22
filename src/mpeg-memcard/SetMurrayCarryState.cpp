// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "murray.h"
#include "clock.h"
#include "asega.h"
extern "C" {
void SetXfKind(void *, XF *, int);
void ResetRunBlendFootsteps(void *);
void RetractAsegaHandle(void *);
void RetractSmaRef(void *);
void ApplyAsegToHandle(float, float, void *, void *, int, void *);
void func_001F1448(void *, void *, int, int, void *);
extern QW g_2a2dd0;
}
/* What SetMurrayCarryState reads of the player past the fields of murray.h: the phase of the carry blend, the time of the last
   state change and the three animation bindings of the carry states. */
struct MURRAYCARRYVIEW {
    u8 unknown_0x0[0x1A0];
    f32 uPhase;
    u8 unknown_0x1A4[0x12B8];
    f32 tStateChange;
    u8 unknown_0x1460[0x4];
    void *pasegState1;
    u8 unknown_0x1468[0xA8];
    void *psm;
    u8 unknown_0x1514[0x8];
    void *pasegState2;
};

void SetMurrayCarryState(MURRAY *m, int carrys)
{
    MURRAYCARRYVIEW *view = (MURRAYCARRYVIEW *)m;
    int old = m->iapasegByIndex;
    if (carrys == old)
        return;
    if (old == 0) {
        SetXfKind(m, m->pxfLinear, 2);
        SetXfKind(m, m->pxfAngular, 2);
    } else if (old >= 0) {
        if (old < 3) {
            ASEGA *pasega = (ASEGA *)m->field_0x1030;
            ASEG *paseg = pasega->paseg;
            view->uPhase = pasega->tLocal / paseg->tLength;
        }
    }
    m->iapasegByIndex = carrys;
    ASEG *paseg = 0;
    void *psm = 0;
    int grfapl = 1;
    float tStart = 0.0f;
    view->tStateChange = g_2dded0.t;
    switch (carrys) {
    case 0:
        SetXfKind(m, m->pxfLinear, 1);
        SetXfKind(m, m->pxfAngular, 1);
        psm = view->psm;
        m->velGoal = g_2a2dd0;
        break;
    case 1:
        paseg = (ASEG *)view->pasegState1;
        tStart = view->uPhase * paseg->tLength;
        ResetRunBlendFootsteps((char *)m + 0x1320);
        grfapl = 9;
        break;
    case 2:
        paseg = (ASEG *)view->pasegState2;
        grfapl = 9;
        tStart = view->uPhase * paseg->tLength;
        break;
    }
    RetractAsegaHandle(&m->field_0x1030);
    RetractSmaRef(&m->field_0x1034);
    ApplyAsegToHandle(tStart, 1.0f, paseg, m, grfapl, &m->field_0x1030);
    func_001F1448(psm, m, -1, grfapl, &m->field_0x1034);
}
