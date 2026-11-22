/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void DeactivateCplcy(struct CPCLOSE *, s32, s32);
s32 SetResetFlag__FP2CM(struct CM *);
void func_0012E460(s32 *);
extern struct CM B_002DDF40;

void bevy_camera_looks_deactivate(struct CPCLOSE *close, s32 arg1, s32 arg2) {
    func_0012E460(&close->lookat);
    SetResetFlag__FP2CM(&B_002DDF40);
    DeactivateCplcy(close, arg1, arg2);
}
