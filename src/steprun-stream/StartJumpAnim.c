// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "guard.h"

void InitJumper(struct JUMPER *pjumper);
void SetJumperState(struct JUMPER *pjumper, s32 state);

void StartJumpAnim(struct JUMPANIM *pjumpanim, struct STEP *pso, s32 field_0x3C, struct JUMPER *pjumper) {
    if (pjumpanim->pobject != 0) {
        memset(pjumper, 0, 0x70);
        memset(pjumper, 0, 0x70);
        InitJumper(pjumper);
        pjumper->pjumpanim = pjumpanim;
        pjumper->pso = pso;
        pjumper->field_0x3C = field_0x3C;
        SetJumperState(pjumper, 0);
    }
}
