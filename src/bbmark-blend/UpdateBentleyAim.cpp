// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "clock.h"
#include "joy.h"
extern "C" {
int FButtonPressedWithin(JOY *, int, float);
int IsmsFindSmOptional__FP2SM3OID(SM *, int);
void SeekSma(void *, int);
void SetBentleyAimState(BENTLEY *, int);
void ThrowBentleyBomb(BENTLEY *, int);
void UpdateLookRig(void *, int);
int bevy_player_p15_binoc_active(BENTLEY *);
extern float RO_002BC994;
void UpdateBentleyAim(BENTLEY *self) {
    int state;
    do {
        state = self->aimState;
        if (state != -1) {
            if (state >= -1) if (state < 2) {
                if (bevy_player_p15_binoc_active(self) == 0) {
                    SetBentleyAimState(self, -1);
                } else {
                    if (self->aimState == 1) {
                        if (RO_002BC994 < g_2dded0.t - self->field_0x1700) {
                            SetBentleyAimState(self, 0);
                        }
                    } else if (FButtonPressedWithin(self->pjoy, 8, 0.25f) != 0) {
                        ThrowBentleyBomb(self, 0x80000);
                    }
                }
            }
        } else {
            if (bevy_player_p15_binoc_active(self) != 0 && self->binocPhase != 2) {
                if (RO_002BC994 < g_2dded0.t - self->field_0x1700) {
                    SetBentleyAimState(self, 0);
                } else {
                    SetBentleyAimState(self, 1);
                }
            }
            switch ((unsigned int)self->state) {
            case 0:
                UpdateLookRig(self->PvLookRig(), 0);
                if (self->field_0x181C != 0 && self->stateLookRig != -1 && self->field_0x1034 != 0 &&
                    IsmsFindSmOptional__FP2SM3OID(self->psm, 0x17B) >= 0) {
                    SeekSma(self->field_0x1034, 0x17B);
                }
                break;
            case 1: case 2: case 3: case 7:
                UpdateLookRig(self->PvLookRig(), 1);
                break;
            case 5:
                UpdateLookRig(self->PvLookRig(), 2);
                break;
            default:
                UpdateLookRig(self->PvLookRig(), -1);
                break;
            }
        }
    } while (state != self->aimState);
}
}
