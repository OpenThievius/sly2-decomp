/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BLOT, a sprite object of the menus and the job screens (a blot: SetBlotBlots, UpdateBlotMovie, LoadBlotFromBrx): an LO with a
   movie or a streamed record, the label ids it plays (0x70 to 0x78) and a list of up to ten label ids at 0xCC. The two classes
   below (JOBBLOT, RESTARTBLOT) are the blots of the job list and of the restart prompt; their own fields start at 0x110.
   A field is here when two of the functions of the 0x211148 module agree on it or the function is one of the blot's own virtuals
   (Update of the two subclasses, PostLoad, LoadFromBrx). The 8-byte gap at 0x108 stands for fields no function has read.
   BLOTVIEW is the flat view Blot_Construct writes through (it sets the vtable pointer by hand, as a compiler-made constructor
   would). C++ only. */
#ifndef SLY2_BLOT_H
#define SLY2_BLOT_H
#include "types.h"
#include "lo.h"
#include "sl.h"
#include "job.h"

struct BLOTSTREAM;

struct BLOT : LO {
    virtual void Select(s32 selector);  /* 49: called with -1 by SetBlotLabelList, SetBlotLabelListFromRef, PostBlotLoad, JobBlot_Update; PauseMenu_SetState
                                           passes a page's selector words (pausemenu.h) */
    virtual void Hide();                /* 50: JobBlot_Update (when every task is complete), bevy_jobs_restart_current; PauseMenu_Update hides a page's blot */
    /* 0x50 */ s32 field_0x50;          /* LoadBlotFromBrx: LoadMovieDictionary writes it */
    /* 0x54 */ s32 field_0x54;          /* the same */
    /* 0x58 */ s32 blots;               /* SetBlotBlots' state: LoadBlotFromBrx sets 0 (streamed) or 1 (movie); Blot_Show, bevy_jobs_restart_current test 2 */
    /* 0x5C */ f32 time;                /* bevy_jobs_restart_current: the prompt waits 0.5 s after it */
    u8 unknown_0x60[0xD];
    /* 0x6D */ u8 field_0x6D;           /* PostBlotLoad selects -1 when it is set */
    u8 unknown_0x6E[0x2];
    /* 0x70 */ s32 labelVisible;        /* Blot_Show, LoadBlotFromBrx (0x310) */
    /* 0x74 */ s32 labelAppear;         /* the same (0x30F) */
    /* 0x78 */ s32 labelDisappear;      /* the same (0x311) */
    /* 0x7C */ s32 cur;                 /* Blot_Construct, LoadBlotFromBrx set -1 */
    u8 unknown_0x80[0x4];
    /* 0x84 */ s32 asprite;             /* Blot_Show passes it to FSpriteHasLabel */
    u8 unknown_0x88[0x8];
    /* 0x90 */ f32 dwell;               /* LoadBlotFromBrx reads it from the stream */
    /* 0x94 */ s32 height;              /* LoadBlotFromBrx, PostBlotLoad */
    /* 0x98 */ s32 width;               /* the same */
    /* 0x9C */ f32 field_0x9C;          /* PostBlotLoad: 2048 minus half the height scaled to 640 */
    /* 0xA0 */ f32 field_0xA0;          /* PostBlotLoad: 2048 minus half the width scaled by 0.4545 */
    u8 unknown_0xA4[0x4];
    /* 0xA8 */ s32 field_0xA8;          /* PostBlotLoad sets -1 */
    u8 unknown_0xAC[0x10];
    /* 0xBC */ s32 field_0xBC;          /* LoadBlotFromBrx reads it from the stream; PostBlotLoad finds the world's font when it is set */
    /* 0xC0 */ BLOTSTREAM *pstream;     /* LoadBlotFromBrx: the streamed record */
    /* 0xC4 */ void *palloc;            /* LoadBlotFromBrx: B_003E1C70 (streamed) or B_003E1C80 (movie) */
    /* 0xC8 */ BLOT *pblotSelf;         /* PostBlotLoad */
    /* 0xCC */ s32 alabel[10];          /* SetBlotLabelList copies up to ten ids in, SetBlotLabelListFromRef fills it; Blot_Construct sets -1 */
    u8 unknown_0xF4[0x8];
    /* 0xFC */ SL sl;                   /* Blot_Construct: InitSl(.., 0x68) */
    u8 unknown_0x108[0x8];
};

/* what LoadBlotFromBrx allocates (0x50 bytes) for a streamed blot: it points back at the blot at 0x40 */
struct BLOTSTREAM {
    u8 unknown_0x0[0x40];
    /* 0x40 */ BLOT *pblot;
    u8 unknown_0x44[0xC];
};

/* the job list's blot: its Update counts the tasks of two lists. A slot holds a task and a word nobody reads. */
struct TASKSLOT {
    TASK *ptask;
    s32 field_0x4;
};
struct JOBBLOT : BLOT {
    /* 0x110 */ s32 ctaskB;             /* JobBlot_Update */
    u8 unknown_0x114[0x4];
    /* 0x118 */ TASKSLOT ataskB[15];
    u8 unknown_0x190[0x4];
    /* 0x194 */ s32 ctaskA;
    u8 unknown_0x198[0x4];
    /* 0x19C */ TASKSLOT ataskA[1];
};

/* the restart prompt's blot */
struct RESTARTBLOT : BLOT {
    /* 0x110 */ s32 field_0x110;        /* bevy_jobs_restart_current sets 1 on every update */
    /* 0x114 */ s32 field_0x114;        /* tested for 0 before the world's current job is restarted */
};

/* the flat view of a BLOT for Blot_Construct: words 0 and 4 are BASIC's, the vtable pointer at 0xC */
struct BLOTVIEW {
    s32 field_0x0;
    s32 field_0x4;
    u8 unknown_0x8[0x4];
    void *vtable;
    u8 unknown_0x10[0x7C - 0x10];
    s32 cur;
    u8 unknown_0x80[0xCC - 0x80];
    s32 alabel[10];
    u8 unknown_0xF4[0x8];
    SL sl;
};
#endif
