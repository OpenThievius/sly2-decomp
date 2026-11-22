// SPDX-License-Identifier: GPL-3.0-or-later
// UpdateMurrayActive: per-frame state update of Murray's active states.
#include "murray.h"
#include "joy.h"
/* The player's jump part (InitJmp, at 0x2C0 of the player); only the words this update reads. */
struct JMP {
    u8 unknown_0x0[0x4];
    s32 state;
    u8 unknown_0x8[0x14];
    s32 cjump;
};

extern "C" {
extern float g_2dded0;
extern float D_002C08DC;
extern float D_002C08E0;
void CarryThrow_Update(void *);
void ClearVjoyPresses(JOY *, int);
int FAsegaGone(void *);
int FAttachGroundTarget(void *, int, int);
int FButtonPressedWithin(JOY *, int, float);
int FJtInFocusRange(MURRAY *, int);
int FJtLandsWithin(MURRAY *, float);
int FMurrayAttackCanChain(MURRAY *);
int FMurrayTryGrabGuard(MURRAY *);
int FSmaRetracted(void *);
int GrfbtnJtGadget(MURRAY *, int);
int GrfbtnVjoyPressedWithin(JOY *, int, float);
void SetJmpState(void *, int, int, int);
void SetMurrayState(MURRAY *, int);
void StartBinoc(void *, int, int, int);
void StartMurrayAttackA(MURRAY *);
void StartMurrayAttackB(MURRAY *);
void UpdateAttachInput(void *);
void UpdateJmpBodyState(void *);
void UpdateJtActivePipe(void *);
void UpdateMurrayAttack(MURRAY *);
void UpdateMurrayCarry(MURRAY *);
void UpdateMurrayLift(MURRAY *);
void UpdateMurrayMash(MURRAY *);
void UpdateZap(void *);
void func_001B5990(MURRAY *);
void func_001B6BA8(MURRAY *);
void func_001B8EC0(MURRAY *);

void UpdateMurrayActive(MURRAY *pmurray)
{
    int murraysStart;
    do {
        murraysStart = pmurray->state;
        switch (murraysStart) {
        case 2: case 3: case 4: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17: case 18: case 20:
            break;
        default:
            if (g_2dded0 - pmurray->tJump > 0.1f) {
                switch (pmurray->state) {
                case 5:
                    SetJmpState(pmurray->PvJmp(), 16, 0, 0);
                    break;
                case 12:
                    if (pmurray->field_0x1840 == 3)
                        SetJmpState(pmurray->PvJmp(), 11, 0, 0);
                    break;
                case 13:
                    if (pmurray->attachKind != 1 && pmurray->attachKind != 12)
                        SetJmpState(pmurray->PvJmp(), 0, 0, 0);
                    break;
                default:
                    SetJmpState(pmurray->PvJmp(), 0, 0, 0);
                    break;
                }
            }
            break;
        }

        switch (pmurray->state) {
        case 0: case 1: case 10:
            if (!(pmurray->pjoy->grfbtn & 8) && FJtInFocusRange(pmurray, 0)) {
                SetMurrayState(pmurray, 9);
            } else if (FButtonPressedWithin(pmurray->pjoy, 0x40, 0.1f)) {
                SetJmpState(pmurray->PvJmp(), 1, 0, 0);
            } else if (GrfbtnVjoyPressedWithin(pmurray->pjoy, 0x400, 0.15f) &&
                       pmurray->FCanUseGadget(3)) {
                ClearVjoyPresses(pmurray->pjoy, 0x400);
                StartBinoc(((char *)pmurray + 0xF00), 0, 0, 0);
            } else if (FMurrayAttackCanChain(pmurray) &&
                       FButtonPressedWithin(pmurray->pjoy, 0x10, D_002C08DC)) {
                StartMurrayAttackB(pmurray);
            } else if (!FMurrayTryGrabGuard(pmurray)) {
                if (FButtonPressedWithin(pmurray->pjoy, 0x20, 0.2f)) {
                    if (!FAttachGroundTarget(pmurray->PvAttach(), 0xF8FA, 0) && pmurray->field_0x13EC) {
                        pmurray->field_0x144C = 0;
                        SetMurrayState(pmurray, 4);
                    }
                } else if (FMurrayAttackCanChain(pmurray) &&
                           FButtonPressedWithin(pmurray->pjoy, 0x80, D_002C08DC)) {
                    StartMurrayAttackA(pmurray);
                } else {
                    float uStick = pmurray->pjoy->uStick;
                    if (pmurray->state == 0 ? uStick > 0.1f : uStick > 0.0f) {
                        if (pmurray->pjoy->grfbtn & 8)
                            SetMurrayState(pmurray, 1);
                        else
                            SetMurrayState(pmurray, 10);
                    } else {
                        SetMurrayState(pmurray, 0);
                    }
                }
            }
            break;
        case 2: {
            UpdateJmpBodyState(pmurray->PvJmp());
            switch (((JMP *)((char *)pmurray + 0x2C0))->state) {
            case 0: case 11: case 15: case 16:
                break;
            default:
                if (GrfbtnVjoyPressedWithin(pmurray->pjoy, 0x90, D_002C08DC) &&
                    pmurray->FCanUseGadget(2)) {
                    int cjump = ((JMP *)((char *)pmurray + 0x2C0))->cjump;
                    if (cjump < 6) {
                        if (cjump > 0 && !FJtLandsWithin(pmurray, D_002C08E0)) {
                            ClearVjoyPresses(pmurray->pjoy, 0x90);
                            pmurray->field_0x13E8 = 0;
                            SetMurrayState(pmurray, 3);
                        }
                    }
                }
                break;
            }
            break;
        }
        case 13:
            UpdateAttachInput(pmurray->PvAttach());
            break;
        case 14:
            UpdateZap(((char *)pmurray + 0xDF0));
            break;
        case 3:
            func_001B6BA8(pmurray);
            break;
        case 5:
            UpdateMurrayCarry(pmurray);
            break;
        case 6:
            UpdateMurrayMash(pmurray);
            break;
        case 4:
            UpdateMurrayLift(pmurray);
            break;
        case 7: case 8:
            if (FAsegaGone(pmurray->field_0x1030))
                SetMurrayState(pmurray, 0);
            break;
        case 11:
            UpdateMurrayAttack(pmurray);
            break;
        case 9:
            func_001B5990(pmurray);
            break;
        case 12:
            func_001B8EC0(pmurray);
            break;
        case 15:
            CarryThrow_Update(((char *)pmurray + 0x1910));
            break;
        case 20:
            UpdateJtActivePipe(pmurray->PvPipe());
            break;
        case 17:
            if (pmurray->field_0x1030 && FAsegaGone(pmurray->field_0x1030))
                SetMurrayState(pmurray, 0);
            else if (pmurray->field_0x1034 && FSmaRetracted(pmurray->field_0x1034))
                SetMurrayState(pmurray, 0);
            break;
        case 21:
            if (FButtonPressedWithin(pmurray->pjoy, 0x40, 0.0f))
                SetJmpState(pmurray->PvJmp(), 13, 0, 0);
            else if (!(pmurray->pjoy->grfbtn & GrfbtnJtGadget(pmurray, 0x10)))
                SetMurrayState(pmurray, 0);
            break;
        }
    } while (pmurray->state != murraysStart);
}
}
