// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "murray.h"
#include "clock.h"
extern "C" {
void SetXfKind(void *, XF *, int);
void ResetRunBlendFootsteps(void *);
void RetractAsegaHandle(void *);
void RetractSmaRef(void *);
void ApplyAsegToHandle(float, float, void *, void *, int, void *);
void func_001F1448(void *, void *, int, int, void *);
extern QW g_2a2dd0;
}
/* What func_001B5D30 reads of the player past the fields of murray.h: the time of the last focus change and the animation bindings
   of the focus states. */
struct MURRAYFOCUSVIEW {
    u8 unknown_0x0[0x1634];
    void *pasegFocus1;
    u8 unknown_0x1638[0xA8];
    void *psm;
    u8 unknown_0x16E4[0x10C];
    void *pasegFocus2;
    u8 unknown_0x17F4[0x4];
    f32 tFocusChange;
};

extern "C" void func_001B5D30(MURRAY *m, int focus)
{
    MURRAYFOCUSVIEW *view = (MURRAYFOCUSVIEW *)m;
    if (focus == m->field_0x17F4)
        return;
    if (m->field_0x17F4 == 0) {
        SetXfKind(m, m->pxfLinear, 2);
        SetXfKind(m, m->pxfAngular, 2);
    }
    m->field_0x17F4 = focus;
    void *paseg = 0;
    void *psm = 0;
    int grfapl = 1;
    view->tFocusChange = g_2dded0.t;
    switch (focus) {
    case 0:
        SetXfKind(m, m->pxfLinear, 1);
        SetXfKind(m, m->pxfAngular, 1);
        psm = view->psm;
        m->velGoal = g_2a2dd0;
        break;
    case 2:
        paseg = view->pasegFocus2;
        grfapl = 9;
        break;
    case 1:
        paseg = view->pasegFocus1;
        ResetRunBlendFootsteps(m->runBlendD);
        grfapl = 9;
        break;
    }
    RetractAsegaHandle(&m->field_0x1030);
    RetractSmaRef(&m->field_0x1034);
    ApplyAsegToHandle(0.0f, 1.0f, paseg, m, grfapl, &m->field_0x1030);
    func_001F1448(psm, m, -1, grfapl, &m->field_0x1034);
}
