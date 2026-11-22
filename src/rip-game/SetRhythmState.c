/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "clock.h"

struct RHYTHM_153128 {
    u8 unknown_0x0[0x50];
    s32 mode;
    f32 tMode;
    u8 unknown_0x58[0x168];
    s32 cnote;
};

void ClearHandsOff(void *, s32);
void SetHandsOff(void *, s32);
extern char B_003DD490[];

void SetRhythmState(struct RHYTHM_153128 *rhythm, s32 mode) {
    s32 modeOld;

    modeOld = rhythm->mode;
    if (modeOld != mode) {
        if (modeOld == 1) {
            ClearHandsOff(B_003DD490, 3);
        }
        rhythm->mode = mode;
        rhythm->tMode = g_2dded0.t;
        rhythm->cnote = 0;
        if (mode == 1) {
            SetHandsOff(B_003DD490, 3);
        }
    }
}
