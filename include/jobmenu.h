/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JOBMENU, the job list menu (retail's B_003DA3C0, constructed by JobMenu_Construct on top of Menu_Construct): a MENU with two pages
   (0 the jobs, 1 the tasks of the chosen job) whose rows hold a JOB or a TASK and the blot labels drawn for them. Fields from the
   matched JobMenu_* functions (SetPage, SetDirection, Update, UpdateBlot) and func_001DDEA0/func_001DDF00, which agree. C++. */
#ifndef SLY2_JOBMENU_H
#define SLY2_JOBMENU_H
#include "menu.h"
#include "job.h"

struct JOBROW {
    union {
        struct JOB *pjob;   /* page 0: the job (JobMenu_UpdateBlot passes it to FEndTaskComplete) */
        struct TASK *ptask; /* page 1: the task (FTaskComplete) */
    };
    /* 0x4 */ s32 label;      /* JobMenu_UpdateBlot: the row's label slot */
    /* 0x8 */ s32 labelDone;  /* the completion mark's slot */
};

struct JOBMENU : MENU {
    /* 0x40 */ s32 page;      /* -1 closed, 0 jobs, 1 tasks: JobMenu_SetPage, JobMenu_Update, JobMenu_UpdateBlot */
    /* 0x44 */ f32 tPage;     /* the real time the page changed: JobMenu_SetPage */
    /* 0x48 */ s32 cent;      /* the number of rows: SetPage, SetDirection, Update, UpdateBlot, func_001DDEA0 */
    /* 0x4C */ JOBROW aent[16];
    /* 0x10C */ s32 crowMax;  /* the rows one page shows: JobMenu_SetPage sets 10 or 4 */
    /* 0x110 */ struct JOB *pjobSel; /* JobMenu_SetPage: the job whose tasks page 1 lists (B_003E0F9C, the world's current job, when no row is chosen) */
    /* 0x114 */ s32 fFromJobs; /* JobMenu_SetPage sets it when page 1 was entered from page 0; JobMenu_Update */
    /* 0x118 */ s32 isel;     /* the selected row: SetPage, SetDirection (index), UpdateBlot */
    /* 0x11C */ s32 labelHolder0; /* JobMenu_SetPage clears the three when the menu closes */
    /* 0x120 */ s32 labelHolder1;
    /* 0x124 */ s32 labelHolder2;
};
#if defined(__mips__)
SLY2_SIZE_CHECK(JOBMENU, 0x128);
SLY2_OFFSET_CHECK(JOBMENU, isel, 0x118);
SLY2_OFFSET_CHECK(JOBMENU, crowMax, 0x10C);
#endif
#endif
