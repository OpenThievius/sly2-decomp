// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "clock.h"
#include "rhythm.h"
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
            if (note->time + self->windowLate < now) {
                note->fDone = 1;
                if (note->fHit == 0) {
                    PlayDancerMove(note->pdancer, note->btn, note->oid, 2);
                    AddRhythmScore(self, self->scoreMissed);
                }
                break;
            }
        }
        break;
    }
    f32 dt = g_2dded0.dt;
    self->smooth = GSmooth__FfffP3SMPPf(self->smoothState, 0, self->smooth, self->mean, dt);
    UpdateRhythmCrowd(self);
}
}
