/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RHYTHM, the rhythm minigame's controller: an LO (UpdateRhythm calls UpdateLo first; its size 0x50 is where the fields start).
   Its state (mode) is set by SetRhythmState and read by UpdateRhythm and UpdateDancer. Its size is not known. */
#ifndef SLY2_RHYTHM_H
#define SLY2_RHYTHM_H
#include "lo.h"

struct DANCER;

/* a cue: when `time` passes, `pdancer` plays the move for `btn` (UpdateRhythm, QueueRhythmCue, JudgeRhythmPress) */
struct RHYTHMNOTE {
    /* 0x0 */ struct DANCER *pdancer;  /* UpdateRhythm passes it to PlayDancerMove; JudgeRhythmPress reads it (as target) */
    /* 0x4 */ s32 btn;                 /* the button of the move: PlayDancerMove's second argument */
    /* 0x8 */ s32 oid;                 /* PlayDancerMove's third argument */
    /* 0xC */ f32 time;                /* UpdateRhythm compares it with the clock; JudgeRhythmPress reads it */
    u8 unknown_0x10[0x4];
    /* 0x14 */ s32 fPlayed;            /* UpdateRhythm (mode 1) */
    /* 0x18 */ s32 fAnnounced;         /* UpdateRhythm (mode 2: set when the cue starts) */
    /* 0x1C */ s32 fHit;               /* UpdateRhythm (tests it) and JudgeRhythmPress (same offset) */
    /* 0x20 */ s32 fDone;              /* UpdateRhythm (set when the window closes), JudgeRhythmPress */
};

struct RHYTHM : LO {
    /* 0x50 */ s32 mode;                 /* SetRhythmState (sets), UpdateRhythm (switch), UpdateDancer (0 idle, 2 judging) */
    u8 unknown_0x54[0x16C];
    /* 0x1C0 */ s32 cnote;               /* SetRhythmState clears it; UpdateRhythm, QueueRhythmCue */
    /* 0x1C4 */ RHYTHMNOTE anote[3];     /* UpdateRhythm, QueueRhythmCue (3 cues), JudgeRhythmPress */
    /* 0x230 */ s32 btnCue;              /* UpdateRhythm sets it from the cue's btn; JudgeRhythmPress reads it */
    u8 unknown_0x234[0x50];
    /* 0x284 */ f32 mean;                /* AddRhythmScore, ResetRhythmScore (clears), UpdateRhythm (smoothing target) */
    /* 0x288 */ f32 smooth;              /* ResetRhythmScore, UpdateRhythmCrowd, UpdateRhythm (smoothed value) */
};
#endif
