#include "dancer.h"
#include "rhythm.h"
extern "C" {
void AddRhythmScore(RHYTHM *, float);
int FFloatsNear__Ffff(float, float, float);
int FVjoyButtonPressed(JOY *, int);
float GAccuracyRhythmCue(RHYTHM *, RHYTHMNOTE *);
int GrfbtnVjoyPressedWithin(JOY *, int, float);
float MarkClockTickRealOnly__FP5CLOCK(void *);
void PlayDancerMove(DANCER *, int, int, int);
void bevy_camera_follow_activity(void *, int, void *);
float func_00153638(RHYTHM *, float);
extern char B_002DEB30[];
extern char B_003DD040[];
void JudgeRhythmPress(RHYTHM *self, DANCER *dancer) {
    JOY *pjoy = dancer->pjoy;
    int pressed = GrfbtnVjoyPressedWithin(pjoy, 0xF0, 0.0f);
    self->btnCue = pressed;
    if (pressed != 0) {
        for (int index = 0; index < self->cnote; index++) {
            RHYTHMNOTE *entry = &self->anote[index];
            if (entry->pdancer == dancer) {
                if (entry->fDone == 0) {
                    bevy_camera_follow_activity(B_002DEB30, 0x35, self);
                    if (MarkClockTickRealOnly__FP5CLOCK(B_003DD040) < entry->time - self->windowEarly) {
                        PlayDancerMove(dancer, -1, -1, 1);
                        AddRhythmScore(self, self->scoreTooEarly);
                        return;
                    }
                    if (entry->fHit != 0) {
                        PlayDancerMove(dancer, -1, -1, 1);
                        AddRhythmScore(self, self->scoreRepeat);
                        return;
                    }
                    entry->fHit = 1;
                    if (FVjoyButtonPressed(pjoy, entry->btn) != 0) {
                        int cellIndex = 0;
                        PlayDancerMove(dancer, entry->btn, entry->oid, 0);
                        AddRhythmScore(self, func_00153638(self, GAccuracyRhythmCue(self, entry)));
                        for (; cellIndex < self->cbeat; cellIndex++) {
                            RHYTHMBEAT *cell = &self->abeat[cellIndex];
                            if (FFloatsNear__Ffff(cell->time, entry->time, 0.1f) != 0) {
                                cell->hit = 1;
                                break;
                            }
                        }
                    } else {
                        PlayDancerMove(dancer, -1, -1, 1);
                        AddRhythmScore(self, self->scoreWrongButton);
                    }
                    return;
                }
            }
        }
    }
}
}
