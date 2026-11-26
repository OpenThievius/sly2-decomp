// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "guard.h"
extern "C" void StopAnimref(ANIMREF *);
extern "C" void StartAnimref(ANIMREF *, STEPGUARD *, int, float);
extern "C" float GRandInRange(float, float);
extern "C" void func_0020AC28(STEPGUARD *, AIMSTATE *, int, QW);
extern float g_2dded0;
extern "C" const float RO_FLT_002A88C4;
void func_0020AB68(STEPGUARD *self, AIMSTATE *anim, int mode, QW vec) {
    if (self->paimstate) {
        StopAnimref(self->paimstate->panimref);
        AIMSTATE *old = self->paimstate;
        float base = g_2dded0;
        float wait = base + GRandInRange(old->field_0x60, old->field_0x64);
        self->paimstate = 0;
        self->tCooldown = wait;
    }
    self->paimstate = anim;
    if (anim) {
        ANIMREF *clip = anim->panimref;
        StartAnimref(clip, self, clip->grf | 1, 0.0f);
        self->tCooldown = RO_FLT_002A88C4;
    }
    func_0020AC28(self, anim, mode, vec);
}
