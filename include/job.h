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
    /* 0x58 */ f32 tState;          /* readers: ApplyTaskState stores the clock when the state changes, UpdateTask measures the time limit from it */
    /* 0x5C */ s32 labelId;         /* EnterTask shows the HUD label (ShowHudLabel), LeaveTask clears it */
    /* 0x60 */ s32 labelFlag;       /* EnterTask, LeaveTask: the label is only used when set */
    /* 0x64 */ s32 cEnter;          /* EnterTask counts; readers: PostLoadTask and RestoreTaskStateFromSave (from the save), ApplyTaskState clears it */
    /* 0x68 */ s32 cComplete;       /* readers: PostLoadTask (from the save), ApplyTaskState counts it on state 2 */
    /* 0x6C */ s32 field_0x6C;      /* reader: FTaskPrerequisitesDone (a task in state 1 with it set counts as done) */
    /* 0x70 */ s32 field_0x70;      /* reader: ApplyTaskState (state 1 with it set switches to the task) */
    /* 0x74 */ s32 field_0x74;      /* reader: ApplyTaskState (state 1 with it set records the task's id) */
    /* 0x78 */ f32 tLimit;          /* readers: PostLoadTask, UpdateTask (the time limit; SendTaskTimeLimit fires when it runs out) */
    /* 0x7C */ struct JOB *job;     /* EnterTask, RefuseTaskState (virtual calls on it), PostTaskJobEvent */
    /* 0x80 */ struct LO *ploMarker; /* readers: PostLoadTask (tested), UpdateTask (Add while the task is in state 1, else Remove) */
    u8 unknown_0x84[0xC];
    /* 0x90 */ s32 *aoidPrereq;     /* readers: LoadTaskFromBrx (reads the ids), PostLoadTask (resolves them into aprereq) */
    /* 0x94 */ s32 cprereq;         /* readers: LoadTaskFromBrx, PostLoadTask, CollectTaskPrerequisites, FTaskPrerequisitesDone, ... */
    /* 0x98 */ struct TASK **aprereq; /* the same */
    /* 0x9C */ s32 *aoidDep;        /* readers: LoadTaskFromBrx, PostLoadTask (resolves them into adep) */
    /* 0xA0 */ s32 cdep;            /* readers: LoadTaskFromBrx, PostLoadTask, SetTaskStateCascade, VisitTaskInOrder */
    /* 0xA4 */ struct TASK **adep;  /* the same */
    /* 0xA8 */ s32 ctoggle;         /* EnterTask, LeaveTask pass ctoggle and atoggle to ApplyTaskToggles */
    /* 0xAC */ void *atoggle;
    /* 0xB0 */ s32 canim;           /* AddTaskAnim (limit 0x20), EnterTask, LeaveTask pass canim and aanim to ApplyTaskAnims */
    /* 0xB4 */ struct ANIMREC *aanim;
    /* 0xB8 */ s32 oidSpawn;        /* EnterTask: when not -1 the task is the world's restart task (NotifyJobTaskState reads it) */
    /* 0xBC */ s32 levelRow;        /* readers: RestartAtTask (level row of the restart), InitTask (-1) */
    /* 0xC0 */ s32 field_0xC0;      /* readers: RestartAtTask, func_00165280 (a value other than -1 goes through func_001D8B20), InitTask (-1) */
    /* 0xC4 */ struct LO *plo;      /* EnterTask: the warp it starts (Warp_Start) after marking its entry */
    /* 0xC8 */ s32 pathEnter[2];    /* readers: PostLoadTask (its first word non-zero: cEnter comes from the save) */
    /* 0xD0 */ s32 pathComplete[2]; /* readers: PostLoadTask (the same for cComplete) */
    /* 0xD8 */ s32 pathSave[2];    /* FTaskComplete: its first word non-zero means a path into the game save */
    /* 0xE0 */ s32 pathState[2];    /* reader: RestoreTaskStateFromSave (the saved state) */
    /* 0xE8 */ s32 pathForced[2];   /* reader: RestoreTaskStateFromSave (the forced flag) */
    /* 0xF0 */ s32 pending;         /* readers: CollectTaskPrerequisites (-1 = not queued, else the state it is queued for), UpdateDependentTaskState, InitTask (-1) */
    /* 0xF4 */ s32 cause;           /* FTaskRunning: 2 and 3 are not running; EnterTask and LeaveTask pass it to ApplyTaskAnims; the CAUSESCOPE of
                                       ForceTaskState, RequestTaskState, VisitTaskInOrder saves and sets it (the JOB has the pair at 0xF0) */
    /* 0xF8 */ s32 causeArg;        /* the same scope's argument */
    /* 0xFC */ s32 cVisit;          /* readers: OrderTasks (clears it), VisitTaskInOrder (counts the visits against cprereq) */
    /* 0x100 */ s32 depthMax;       /* reader: VisitTaskInOrder */
    /* 0x104 */ s32 jobDepthMax;    /* reader: VisitTaskInOrder */
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
    /* 0x50 */ s32 disabled;            /* reader: OnJobEvent (JOB's own event handler): a job with it set restarts on event 0x10 */
    /* 0x54 */ s32 cevFail;             /* reader: OnJobEvent: the events that fail the job */
    /* 0x58 */ s32 *aevFail;            /* the same, the list */
    /* 0x5C */ s32 cevComplete;         /* reader: OnJobEvent: the events that complete the job */
    /* 0x60 */ s32 *aevComplete;        /* the same, the list */
    /* 0x64 */ struct TASK *ptaskStart; /* NotifyJobTaskState activates the job when this task reports; bevy_jobs_162df8 restarts at it */
    /* 0x68 */ struct TASK *ptaskEnd;   /* NotifyJobTaskState begins the completion; FEndTaskComplete, PublishJobEnd */
    /* 0x6C */ s32 field_0x6C;          /* InitJob sets -1 */
    /* 0x70 */ s32 field_0x70;          /* InitJob sets -1 */
    u8 unknown_0x74[0x4];
    /* 0x78 */ s32 field_0x78;          /* PublishJobEnd: when 0 it sets the end task's state and autosaves */
    /* 0x7C */ s32 count;               /* reader: StartJob adds 1 (JOB's own function) */
    /* 0x80 */ struct SLLIST sllist;    /* InitJob */
    /* 0x8C */ s32 ctoggle;             /* readers: StartJob, StopJob pass ctoggle and atoggle to ApplyTaskToggles (two agree) */
    /* 0x90 */ void *atoggle;
    /* 0x94 */ s32 canim;               /* readers: StartJob, StopJob pass canim, aanim and cause to ApplyTaskAnims (two agree) */
    /* 0x98 */ void *aanim;
    /* 0x9C */ f32 field_0x9C;          /* InitJob sets 480.0f */
    /* 0xA0 */ f32 field_0xA0;          /* InitJob sets 720.0f */
    u8 unknown_0xA4[0x8];
    /* 0xAC */ s32 field_0xAC;          /* InitJob sets -1; SetJobCompleteAseg */
    /* 0xB0 */ s32 field_0xB0;          /* same */
    /* 0xB4 */ s32 field_0xB4;          /* same */
    /* 0xB8 */ void *field_0xB8;        /* BeginJobComplete: non-null starts the end sequence */
    u8 unknown_0xBC[0x34];
    /* 0xF0 */ s32 cause;               /* readers: StartJob, StopJob (the last argument of ApplyTaskAnims) */
    /* 0xF4 */ s32 causeArg;            /* readers: ForceTaskState, RequestTaskState (the CAUSESCOPE's job half saves and sets the pair) */
};
#endif
