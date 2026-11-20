// SPDX-License-Identifier: GPL-3.0-or-later
#include "murray.h"

/* The controller as UpdateMurrayAttack reads it: the stick value at 0x1C. */
struct JOY {
    u8 unknown_0x0[0x1C];
    /* 0x1C */ f32 field_0x1C;
};

extern "C" {
int FAsegaGone(void *pasega);
int FButtonPressedWithin(JOY *pjoy, int grfbtn, float dt);
int FMurrayAttackCanChain(MURRAY *pmurray);
int FMurrayTryGrabGuard(MURRAY *pmurray);
void SetMurrayAttackState(MURRAY *pmurray, int attackState);
void SetMurrayState(MURRAY *pmurray, int state);
void EndMurrayAttack(MURRAY *pmurray);

void UpdateMurrayAttack(MURRAY *pmurray)
{
    s32 attackStatePrevious;
    for (;;) {
        attackStatePrevious = pmurray->field_0x1810;
        if (pmurray->field_0x1030 == 0 || FAsegaGone(pmurray->field_0x1030) != 0) {
            SetMurrayState(pmurray, 0);
        } else {
            switch (pmurray->field_0x1810) {
            case 0:
            case 1:
                if (FMurrayAttackCanChain(pmurray) && FButtonPressedWithin(pmurray->pjoy, 0x80, 0.25f)) {
                    SetMurrayAttackState(pmurray, pmurray->field_0x1810 == 0);
                } else if ((!FMurrayAttackCanChain(pmurray) || !FMurrayTryGrabGuard(pmurray)) && pmurray->field_0x181C != 0
                           && pmurray->pjoy->field_0x1C > 0.0f) {
                    EndMurrayAttack(pmurray);
                }
                break;
            case 2:
            case 3:
                if (FMurrayAttackCanChain(pmurray) && FButtonPressedWithin(pmurray->pjoy, 0x10, 0.25f)) {
                    SetMurrayAttackState(pmurray, pmurray->field_0x1810 == 2 ? 3 : 2);
                } else if ((!FMurrayAttackCanChain(pmurray) || !FMurrayTryGrabGuard(pmurray)) && pmurray->field_0x181C != 0
                           && pmurray->pjoy->field_0x1C > 0.0f) {
                    EndMurrayAttack(pmurray);
                }
                break;
            }
        }
        if (pmurray->field_0x1810 == attackStatePrevious || pmurray->field_0x1810 == -1)
            break;
    }
}
}
