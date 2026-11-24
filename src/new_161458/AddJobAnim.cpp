/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct JobAnimEntry_162728 {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
    s32 word4;
    s32 word5;
};

/* The object's class is not recovered (RefCallAddJobAnim passes it from a Splice call): a local view of the two fields. Like a TASK
   (job.h) it keeps a count of up to 0x20 animation entries and a table, and adds nothing while its word at 0x50 is set. */
struct ANIMLIST_162728 {
    u8 unknown_0x0[0x50];
    /* 0x50 */ s32 fBusy;
    u8 unknown_0x54[0x40];
    /* 0x94 */ s32 canim;
    /* 0x98 */ struct JobAnimEntry_162728 *aanim;
};

extern "C" void AddJobAnim(ANIMLIST_162728 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 count;
    struct JobAnimEntry_162728 *entry;

    if (arg0->fBusy == 0) {
        count = arg0->canim;
        if (count < 0x20) {
            arg0->canim = count + 1;
            entry = &arg0->aanim[count];
            entry->word5 = arg5;
            entry->word0 = arg1;
            entry->word1 = arg2;
            entry->word2 = arg3;
            entry->word3 = arg4;
            entry->word4 = 0;
        }
    }
}
