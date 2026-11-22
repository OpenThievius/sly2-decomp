// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "clock.h"
#include "joy.h"
extern "C" {
void CarryThrow_Update(void *);
void ClearVjoyPresses(JOY *, int);
int FAsegaGone(void *);
int FAttachGroundTarget(void *, int, int);
int FButtonPressedWithin(JOY *, int, float);
int FJtInFocusRange(BENTLEY *, int);
int FSmaRetracted(void *);
int GrfbtnVjoyPressedWithin(JOY *, int, float);
BENTLEYSLOT *PslotBentleyGadget(BENTLEY *, int);
void SetBentleyState(BENTLEY *, int);
void SetJmpState(void *, int, int, int);
void StartBinoc(void *, int, int, int);
void UpdateAttachInput(void *);
void UpdateBentleyAim(BENTLEY *);
void UpdateBentleyGadget(BENTLEY *);
void UpdateJmpBodyState(void *);
void UpdateJtActivePipe(void *);
void UpdateZap(void *);
void func_001367D8(BENTLEY *);
extern float D_002BC930;
void UpdateBentleyActive(BENTLEY *self)
{
    unsigned stateOld;
    do {
        stateOld = self->state;
        switch (stateOld) {
        case 2: case 4: case 6: case 8: case 9: case 10: case 11: case 13: case 14:
            break;
        case 3:
            if (self->attachKind != 1 && self->attachKind != 0xC && g_2dded0.t - self->tJump > 0.1f)
                SetJmpState(self->PvJmp(), 0, 0, 0);
            break;
        default:
            if (g_2dded0.t - self->tJump > 0.1f)
                SetJmpState(self->PvJmp(), 0, 0, 0);
            break;
        }
        switch (self->state) {
        case 0: case 1: case 7:
            if (!(self->pjoy->grfbtn & 8) && FJtInFocusRange(self, 0))
                SetBentleyState(self, 5);
            else if (FButtonPressedWithin(self->pjoy, 0x40, 0.1f))
                SetJmpState(self->PvJmp(), 1, 0, 0);
            else if (GrfbtnVjoyPressedWithin(self->pjoy, 0x400, 0.15f) && self->FCanUseGadget(3)) {
                ClearVjoyPresses(self->pjoy, 0x400);
                StartBinoc(self->PvBinoc(), 0, 0, 0);
            } else if (GrfbtnVjoyPressedWithin(self->pjoy, 0x10, 0.15f) && self->FCanUseGadget(self->field_0x1870)) {
                ClearVjoyPresses(self->pjoy, 0x10);
                self->pslotActive = PslotBentleyGadget(self, self->field_0x1870);
                SetBentleyState(self, 6);
            } else if (FButtonPressedWithin(self->pjoy, 0x20, 0.2f))
                FAttachGroundTarget(self->PvAttach(), 0xF8FE, 0);
            else {
                float axis = self->pjoy->uStick;
                if (self->state == 0 ? axis > 0.1f : axis > 0.0f) {
                    if (self->pjoy->grfbtn & 8)
                        SetBentleyState(self, 1);
                    else
                        SetBentleyState(self, 7);
                } else
                    SetBentleyState(self, 0);
            }
            break;
        case 2:
            UpdateJmpBodyState(self->PvJmp());
            if (GrfbtnVjoyPressedWithin(self->pjoy, 0x10, 0.15f) && self->FCanUseGadget(self->field_0x1870)) {
                ClearVjoyPresses(self->pjoy, 0x10);
                self->pslotActive = PslotBentleyGadget(self, self->field_0x1870);
                SetBentleyState(self, 6);
            }
            break;
        case 3:
            UpdateAttachInput(self->PvAttach());
            break;
        case 4:
            UpdateZap(self->PvZap());
            break;
        case 5:
            if (!(self->pjoy->grfbtn & 8) && FJtInFocusRange(self, 1)) {
                if (FButtonPressedWithin(self->pjoy, 0x40, 0.1f))
                    SetJmpState(self->PvJmp(), 1, 0, 0);
                else if (GrfbtnVjoyPressedWithin(self->pjoy, 0x400, 0.15f) && self->FCanUseGadget(3)) {
                    ClearVjoyPresses(self->pjoy, 0x400);
                    StartBinoc(self->PvBinoc(), 0, 0, 0);
                } else if (FButtonPressedWithin(self->pjoy, 0x20, 0.2f))
                    FAttachGroundTarget(self->PvAttach(), 0xF8FE, 0);
                else if (GrfbtnVjoyPressedWithin(self->pjoy, 0x10, 0.15f) && self->FCanUseGadget(self->field_0x1870)) {
                    ClearVjoyPresses(self->pjoy, 0x10);
                    self->pslotActive = PslotBentleyGadget(self, self->field_0x1870);
                    SetBentleyState(self, 6);
                }
            } else
                SetBentleyState(self, 0);
            break;
        case 13:
            UpdateJtActivePipe(self->PvPipe());
            break;
        case 6:
            UpdateBentleyGadget(self);
            break;
        case 8:
            func_001367D8(self);
            break;
        case 12:
            CarryThrow_Update(self->PvCarry());
            break;
        case 10:
            if (self->field_0x1030 == 0 || FAsegaGone(self->field_0x1030) == 0) {
                if (self->field_0x1034 != 0 && FSmaRetracted(self->field_0x1034) != 0)
                    SetBentleyState(self, 0);
            } else
                SetBentleyState(self, 0);
            break;
        case 14:
            if (D_002BC930 < g_2dded0.t - self->tState)
                SetBentleyState(self, 0);
            break;
        }
        UpdateBentleyAim(self);
    } while ((unsigned)self->state != stateOld);
}
}
