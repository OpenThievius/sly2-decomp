// SPDX-License-Identifier: GPL-3.0-or-later
// UpdateMurrayCarry: per-frame update of Murray's carrying states.
#include "sly2.h"
#include "murray.h"
#include "ps2inline.h"
#include "vu0inline.h"
struct JOY { char pad0[0x18]; float radStick; float uStick; char pad1[0x30 - 0x20]; unsigned grfbtn; };
struct CARRIER { char pad[0x180]; LO *lo; };
union VU_SCALE { QW q; VECTOR v; };

extern "C" {
void ClearVjoyPresses(JOY *, int);
void DetachMurrayObject(MURRAY *);
int FButtonPressedWithin(JOY *, int, float);
int FGadgetAcquired(int);
int GrfbtnVjoyPressedWithin(JOY *, int, float);
void SetJmpState(void *, int, int, int);
void SetMurrayCarryState(MURRAY *, int);
void SetMurrayState(MURRAY *, int);
void SetRunBlendU(void *, float);
void SetStepRadTarget(MURRAY *, float);
void StartBinoc(void *, int, int, int);
void UpdateRunBlendFootsteps(void *);
QW func_00204E38(MURRAY *, void *, float);

void UpdateMurrayCarry(MURRAY *pmurray)
{
    VU_SCALE scale;
    int stateStart;
    for (;;) {
        stateStart = pmurray->iapasegByIndex;
        if (stateStart < 3) {
            if (stateStart >= 0) {
                if (((int)(((CARRIER *)pmurray->ploCarried)->lo->grfo >> 60) & 1) == 0) {
                    DetachMurrayObject(pmurray);
                    pmurray->ploCarried = 0;
                    SetMurrayState(pmurray, 0);
                } else if (GrfbtnVjoyPressedWithin(pmurray->pjoy, 0x40, 0.1f) && FGadgetAcquired(0x12)) {
                    ClearVjoyPresses(pmurray->pjoy, 0x40);
                    SetJmpState(((char *)pmurray + 0x2C0), 0xF, 0, 0);
                } else if (FButtonPressedWithin(pmurray->pjoy, 0xA0, 0.0f)) {
                    SetMurrayState(pmurray, 7);
                } else if (FButtonPressedWithin(pmurray->pjoy, 0x10, 0.0f) && *(int *)((char *)pmurray + 0x1438)) {
                    pmurray->field_0x143C = 0;
                    SetMurrayState(pmurray, 8);
                } else if (GrfbtnVjoyPressedWithin(pmurray->pjoy, 0x400, 0.15f) && pmurray->FCanUseGadget(3)) {
                    ClearVjoyPresses(pmurray->pjoy, 0x400);
                    StartBinoc(((char *)pmurray + 0xF00), 0, 0, 0);
                } else {
                    float uStick = pmurray->pjoy->uStick;
                    if (pmurray->iapasegByIndex == 0 ? uStick > 0.1f : uStick > 0.0f) {
                        if ((pmurray->pjoy->grfbtn & 8) && FGadgetAcquired(0x12))
                            SetMurrayCarryState(pmurray, 2);
                        else
                            SetMurrayCarryState(pmurray, 1);
                    } else {
                        SetMurrayCarryState(pmurray, 0);
                    }
                }
            }
        }
        if (pmurray->iapasegByIndex == stateStart || pmurray->state != 5)
            break;
    }

    switch (pmurray->iapasegByIndex) {
    case 0:
        break;
    case 1:
        SetStepRadTarget(pmurray, pmurray->pjoy->radStick);
        SetRunBlendU(((char *)pmurray + 0x1460), pmurray->pjoy->uStick);
        UpdateRunBlendFootsteps(((char *)pmurray + 0x1460));
        break;
    case 2:
        SetStepRadTarget(pmurray, pmurray->pjoy->radStick);
        {
            void *anim = *(void **)((char *)pmurray + 0x1030);
            QW vel = func_00204E38(pmurray, anim, *(float *)((char *)anim + 0x1C));
            scale.q = VectorFromFloat(-1.0f);
            pmurray->velGoal = VectorScaleX(vel, scale.q);
        }
        break;
    }
}
}
