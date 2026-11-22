/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JOB and TASK, the story-mission objects of the 0x161458 module (fields from the readers named).
   A JOB is an LO (retail's vtable at 0xC, 0x50 bytes of LO, InitJob calls InitLo on it); a C source sees the same layout with
   the LO part as an unknown gap. */
#ifndef SLY2_JOB_H
#define SLY2_JOB_H
#include "types.h"
#ifdef __cplusplus
#include "lo.h"
#endif

struct JOB;

struct ANIMREC;
struct LO;

/* A task: an LO (retail's vtable at 0xC, 0x50 bytes of LO) that a job runs (job at 0x7C). Fields from the functions of the
   0x1637E8 module (FTaskRunning, AddTaskAnim, EnterTask, LeaveTask, FTaskComplete, SendTask*), which are methods of the task or
   agree with each other; the path blocks (0xC8, 0xD0, 0xD8) are the 8-byte values RefGetGameSaveValue takes. */
#ifdef __cplusplus
struct TASK : LO {
#else
struct TASK {
    u8 unknown_0x0[0x50];
#endif
    /* 0x50 */ s32 field_0x50;      /* FTaskRunning: a task with it set is not running; AddTaskAnim adds nothing then */
    /* 0x54 */ s32 state;           /* FTaskComplete: -1 = not set (then the save value, if any), 2 and up = complete */
    u8 unknown_0x58[0x4];
    /* 0x5C */ s32 labelId;         /* EnterTask shows the HUD label (ShowHudLabel), LeaveTask clears it */
    /* 0x60 */ s32 labelFlag;       /* EnterTask, LeaveTask: the label is only used when set */
    /* 0x64 */ s32 cEnter;          /* EnterTask counts */
    u8 unknown_0x68[0x14];
    /* 0x7C */ struct JOB *job;     /* EnterTask, RefuseTaskState (virtual calls on it), PostTaskJobEvent */
    u8 unknown_0x80[0x28];
    /* 0xA8 */ s32 ctoggle;         /* EnterTask, LeaveTask pass ctoggle and atoggle to ApplyTaskToggles */
    /* 0xAC */ void *atoggle;
    /* 0xB0 */ s32 canim;           /* AddTaskAnim (limit 0x20), EnterTask, LeaveTask pass canim and aanim to ApplyTaskAnims */
    /* 0xB4 */ struct ANIMREC *aanim;
    /* 0xB8 */ s32 oidSpawn;        /* EnterTask: when not -1 the task is the world's restart task (NotifyJobTaskState reads it) */
    u8 unknown_0xBC[0x8];
    /* 0xC4 */ struct LO *plo;      /* EnterTask: the warp it starts (Warp_Start) after marking its entry */
    u8 unknown_0xC8[0x10];
    /* 0xD8 */ s32 pathSave[2];    /* FTaskComplete: its first word non-zero means a path into the game save */
    u8 unknown_0xE0[0x14];
    /* 0xF4 */ s32 field_0xF4;      /* FTaskRunning: 2 and 3 are not running; EnterTask and LeaveTask pass it to ApplyTaskAnims */
};

/* One animation request of a job's table (0x18 bytes); names from func_00162250, which reads them. */
struct ANIMREC {
    /* 0x00 */ s32 nState;
    /* 0x04 */ s32 oid;
    /* 0x08 */ s32 oidSel;
    /* 0x0C */ s32 oidAnim;
    /* 0x10 */ s32 fGated;
    /* 0x14 */ s32 nLevelRow;
};

/* An intrusive list head, 0xC bytes; InitSl stores the offset of the link inside the entries at 0x8. */
struct SLLIST {
    u8 unknown_0x0[0x8];
    /* 0x8 */ s32 ibLink;
};

#ifdef __cplusplus
struct JOB : LO {
#else
struct JOB {
    u8 unknown_0x0[0x50];
#endif
    u8 unknown_0x50[0x14];
    /* 0x64 */ struct TASK *ptaskStart; /* NotifyJobTaskState activates the job when this task reports; bevy_jobs_162df8 restarts at it */
    /* 0x68 */ struct TASK *ptaskEnd;   /* NotifyJobTaskState begins the completion; FEndTaskComplete, PublishJobEnd */
    /* 0x6C */ s32 field_0x6C;          /* InitJob sets -1 */
    /* 0x70 */ s32 field_0x70;          /* InitJob sets -1 */
    u8 unknown_0x74[0x4];
    /* 0x78 */ s32 field_0x78;          /* PublishJobEnd: when 0 it sets the end task's state and autosaves */
    u8 unknown_0x7C[0x4];
    /* 0x80 */ struct SLLIST sllist;    /* InitJob */
    u8 unknown_0x8C[0x10];
    /* 0x9C */ f32 field_0x9C;          /* InitJob sets 480.0f */
    /* 0xA0 */ f32 field_0xA0;          /* InitJob sets 720.0f */
    u8 unknown_0xA4[0x8];
    /* 0xAC */ s32 field_0xAC;          /* InitJob sets -1; SetJobCompleteAseg */
    /* 0xB0 */ s32 field_0xB0;          /* same */
    /* 0xB4 */ s32 field_0xB4;          /* same */
    /* 0xB8 */ void *field_0xB8;        /* BeginJobComplete: non-null starts the end sequence */
};
#endif
