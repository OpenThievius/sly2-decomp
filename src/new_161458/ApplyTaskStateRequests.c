/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct JOB;
struct LO;
struct SW;
struct TASK;

/* an entry of a job's table of task state requests, 8 bytes */
struct TASKSTATEREQUEST {
    /* 0x0 */ s32 oid;   /* the task's object id, searched with grffso 0x105 */
    /* 0x4 */ s32 state; /* the state RequestTaskState asks for */
};

struct LO *PloFindSwObject_thunk(struct SW *psw, s32 grffso, s32 oid, struct LO *ploContext);
void RequestTaskState(struct TASK *ptask, s32 state, struct JOB *pjob);
extern struct SW B_003DD490;

void ApplyTaskStateRequests(void *unused, s32 crequest, struct TASKSTATEREQUEST *arequest, struct JOB *pjob) {
    struct TASK *ptask;
    s32 remaining;
    struct TASKSTATEREQUEST *prequest;

    if (crequest > 0) {
        prequest = arequest;
        remaining = crequest;
        do {
            ptask = (struct TASK *)PloFindSwObject_thunk(&B_003DD490, 0x105, prequest->oid, (struct LO *)pjob);
            if (ptask != 0) {
                RequestTaskState(ptask, prequest->state, pjob);
            }
            remaining -= 1;
            prequest += 1;
        } while (remaining != 0);
    }
}
