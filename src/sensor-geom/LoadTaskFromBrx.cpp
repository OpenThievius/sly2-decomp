// SPDX-License-Identifier: GPL-3.0-or-later
struct CBinaryInputStream;
#include "alloc.h"
#include "job.h"
extern "C" {
void *CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void LoadLoFromBrx(TASK *, CBinaryInputStream *);
void *PvAllocStackImpl__Fi(ALLOCREQ *);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, void *);
void *PvAllocSwImpl__Fi(ALLOCREQ *);
int S32Read__18CBinaryInputStream(CBinaryInputStream *);
int U8Read__18CBinaryInputStream(CBinaryInputStream *);
void Unknown1__18CBinaryInputStream(CBinaryInputStream *);
}

// Sets the request's alignment through the pointer the allocator is then given.
static inline ALLOCREQ *Aligned(ALLOCREQ *request)
{
    request->cbAlign = 0x10;
    return request;
}

// Retail stores each request's size at 0x10($sp) but its alignment through the register that holds &req for the call
// (`sw $s1, 0x4($s0)`), and keeps &req in two registers (s0 for the first half, s5 copied from it for the second): the
// alignment store goes through an inline helper that takes the request's address, while `req.cbAlign = 0x10` in the body
// folds to 0x14($sp) (score 28). The two counts are separate locals: one shared local adds a copy (`daddu $v1, $v0`)
// before each `sll` and moves the loop-head nop to the other loop (score 16).
extern "C" void LoadTaskFromBrx(TASK *task, CBinaryInputStream *stream)
{
    char frame[0x10];
    ALLOCREQ req;
    int index;
    int secondIndex;
    CStackFrame_Construct(frame);
    req.cb = 0x200;
    task->atoggle = PvAllocStackImpl__Fi(Aligned(&req));
    req.cb = 0x300;
    task->aanim = (ANIMREC *)PvAllocStackImpl__Fi(Aligned(&req));
    LoadLoFromBrx(task, stream);
    req.cb = task->ctoggle * 0x10;
    task->atoggle = PvAllocSwCopyImpl__FiPv(Aligned(&req), task->atoggle);
    req.cb = task->canim * 0x18;
    task->aanim = (ANIMREC *)PvAllocSwCopyImpl__FiPv(Aligned(&req), task->aanim);
    int count = U8Read__18CBinaryInputStream(stream);
    task->cprereq = count;
    req.cb = count * 4;
    task->aprereq = (TASK **)PvAllocSwClearImpl__Fi(Aligned(&req));
    req.cb = task->cprereq * 4;
    task->aoidPrereq = (s32 *)PvAllocSwImpl__Fi(Aligned(&req));
    for (index = 0; index < task->cprereq; index++) {
        task->aoidPrereq[index] = S32Read__18CBinaryInputStream(stream);
    }
    int secondCount = U8Read__18CBinaryInputStream(stream);
    task->cdep = secondCount;
    req.cb = secondCount * 4;
    task->adep = (TASK **)PvAllocSwClearImpl__Fi(Aligned(&req));
    req.cb = task->cdep * 4;
    task->aoidDep = (s32 *)PvAllocSwImpl__Fi(Aligned(&req));
    for (secondIndex = 0; secondIndex < task->cdep; secondIndex++) {
        task->aoidDep[secondIndex] = S32Read__18CBinaryInputStream(stream);
    }
    Unknown1__18CBinaryInputStream(stream);
    CStackFrame_Destructor(frame, 2);
}
