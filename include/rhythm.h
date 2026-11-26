/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RHYTHM, the rhythm minigame's controller: an LO (UpdateRhythm calls UpdateLo first; its size 0x50 is where the fields start).
   Its state (mode) is set by SetRhythmState and read by UpdateRhythm and UpdateDancer. Its size is not known. */
#ifndef SLY2_RHYTHM_H
#define SLY2_RHYTHM_H
#include "lo.h"
#include "sly2.h"

struct DANCER;
struct SMA;

/* a beat of the minigame's track (SetRhythmBeats copies its list in: 0x30 bytes each, the time first, the screen position at 0x10 and a hit flag at 0x20) */
struct RHYTHMBEAT {
    /* 0x0 */ f32 time;                /* SetRhythmBeats (first and last beat give the span), JudgeRhythmPress (the cell whose time is near a cue's) */
    u8 unknown_0x4[0xC];
    /* 0x10 */ VECTOR pos;             /* SetRhythmBeats lays the beats out along x */
    /* 0x20 */ s32 hit;                /* SetRhythmBeats clears it; JudgeRhythmPress sets it for the cell a hit cue matches */
    u8 unknown_0x24[0xC];
};

/* a cheering crowd member the minigame drives (BindRhythmCrowd, UpdateRhythmCrowd, AddRhythmCrowd: 0x1C bytes each) */
struct RHYTHMCROWD {
    /* 0x0 */ s32 oid;                 /* AddRhythmCrowd's first argument; BindRhythmCrowd finds the object by it */
    /* 0x4 */ s32 oidCheer;            /* AddRhythmCrowd's second argument; BindRhythmCrowd, ICheerFromOid */
    /* 0x8 */ struct SMA *link;        /* BindRhythmCrowd (the SMA binding), UpdateRhythmCrowd (FSmaRetracted, SetSmaGoal); AddRhythmCrowd leaves it */
    /* 0xC */ s32 level;               /* AddRhythmCrowd sets -1; BindRhythmCrowd, UpdateRhythmCrowd */
    /* 0x10 */ f32 threshold[3];       /* BindRhythmCrowd fills it; UpdateRhythmCrowd compares each with the smoothed score */
};

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
    u8 unknown_0x54[0x4];
    /* 0x58 */ f32 windowEarly;          /* JudgeRhythmPress: a press earlier than a cue's time minus it is too early */
    /* 0x5C */ f32 windowLate;           /* UpdateRhythm: a cue is missed once its time plus it has passed */
    /* 0x60 */ s32 cbeat;                /* SetRhythmBeats stores the count, JudgeRhythmPress loops over it */
    u8 unknown_0x64[0xC];
    /* 0x70 */ RHYTHMBEAT abeat[6];      /* SetRhythmBeats copies its list here (6 beats up to the cursor words at 0x190); JudgeRhythmPress */
    u8 unknown_0x190[0x30];
    /* 0x1C0 */ s32 cnote;               /* SetRhythmState clears it; UpdateRhythm, QueueRhythmCue */
    /* 0x1C4 */ RHYTHMNOTE anote[3];     /* UpdateRhythm, QueueRhythmCue (3 cues), JudgeRhythmPress */
    /* 0x230 */ s32 btnCue;              /* UpdateRhythm sets it from the cue's btn; JudgeRhythmPress reads it */
    u8 unknown_0x234[0x50];
    /* 0x284 */ f32 mean;                /* AddRhythmScore, ResetRhythmScore (clears), UpdateRhythm (smoothing target) */
    /* 0x288 */ f32 smooth;              /* ResetRhythmScore, UpdateRhythmCrowd, UpdateRhythm (smoothed value) */
    /* 0x28C */ f32 smoothState[1];      /* UpdateRhythm passes its address to GSmooth, which keeps its state here */
    u8 unknown_0x290[0x8];
    /* 0x298 */ f32 scoreTooEarly;       /* JudgeRhythmPress: what AddRhythmScore gets for a press before the early window */
    /* 0x29C */ f32 scoreWrongButton;    /* JudgeRhythmPress: a press of the wrong button */
    /* 0x2A0 */ f32 scoreRepeat;         /* JudgeRhythmPress: a second press for a cue already pressed */
    /* 0x2A4 */ f32 scoreMissed;         /* UpdateRhythm: a cue whose window closed without a hit */
    /* 0x2A8 */ s32 ccrowd;              /* AddRhythmCrowd (bounded by 0x80), BindRhythmCrowd, UpdateRhythmCrowd */
    /* 0x2AC */ RHYTHMCROWD acrowd[0x80]; /* the same three; 0x80 is AddRhythmCrowd's bound */
};
#endif
