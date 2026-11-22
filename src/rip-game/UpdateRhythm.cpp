// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "clock.h"
#include "rhythm.h"
// local view of RHYTHM's span read here only: the judging window, the smoothing state and the miss penalty
struct RHYTHMTIMINGVIEW {
    u8 unknown_0x0[0x5C];
    f32 window;
    u8 unknown_0x60[0x22C];
    f32 smoothState[1];   // 0x28C: the state GSmooth keeps
    u8 unknown_0x290[0x14];
    f32 penalty;          // 0x2A4: what AddRhythmScore gets for a missed cue
};
extern "C" {
void AddRhythmScore(RHYTHM *, f32);
f32 GSmooth__FfffP3SMPPf(void *, s32, f32, f32, f32);
f32 MarkClockTickRealOnly__FP5CLOCK(void *);
void PlayDancerMove(DANCER *, s32, s32, s32);
void UpdateLo();
void UpdateRhythmCrowd(RHYTHM *);
void bevy_camera_follow_activity(void *, s32, RHYTHM *);
extern char B_002DEB30;
extern char B_003DD040;
void UpdateRhythm(RHYTHM *self) {
    RHYTHMTIMINGVIEW *timing = (RHYTHMTIMINGVIEW *)self;
    UpdateLo();
    f32 now = MarkClockTickRealOnly__FP5CLOCK(&B_003DD040);
    switch (self->mode) {
    case 1:
        for (s32 index = 0; index < self->cnote; index++) {
            RHYTHMNOTE *note = &self->anote[index];
            if (note->fPlayed == 0 && note->time < now) {
                PlayDancerMove(note->pdancer, note->btn, note->oid, 0);
                note->fPlayed = 1;
                break;
            }
        }
        break;
    case 2:
        for (s32 index = 0; index < self->cnote; index++) {
            RHYTHMNOTE *note = &self->anote[index];
            if (note->fDone != 0) continue;
            if (note->fAnnounced == 0 && note->time < now) {
                self->btnCue = note->btn;
                bevy_camera_follow_activity(&B_002DEB30, 0x34, self);
                note->fAnnounced = 1;
            }
            if (note->time + timing->window < now) {
                note->fDone = 1;
                if (note->fHit == 0) {
                    PlayDancerMove(note->pdancer, note->btn, note->oid, 2);
                    AddRhythmScore(self, timing->penalty);
                }
                break;
            }
        }
        break;
    }
    f32 dt = g_2dded0.dt;
    self->smooth = GSmooth__FfffP3SMPPf(timing->smoothState, 0, self->smooth, self->mean, dt);
    UpdateRhythmCrowd(self);
}
}
