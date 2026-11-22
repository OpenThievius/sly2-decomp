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

/* A task: the job that runs it at 0x7C. */
struct TASK {
    u8 unknown_0x0[0xB8];
    /* 0xB8 */ s32 field_0xB8; /* NotifyJobTaskState compares it with -1 before SetSwRestartTask */
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
