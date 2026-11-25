#include "cref.h"
#include "job.h"
#include "sw.h"
extern "C" SW B_003DD490;
extern "C" int B_003D4A60;
extern "C" void PostLoLoad(TASK *);
extern "C" void AppendSlEntry(SLLIST *, TASK *);
extern "C" int FIsCurrentTask(TASK *);
extern "C" int FTaskRunning(TASK *);
extern "C" void ApplyTaskToggles(TASK *, int, int, void *);
extern "C" void ApplyTaskAnims(TASK *, int, int, ANIMREC *, int);
extern "C" CRef RefGetGameSaveValue(void *, int *);
extern "C" TASK *PloFindSwObject_thunk(SW *, int, int, int);
extern "C" void func_001A6CA8(TASK *, int);
extern "C" void PostLoadTask(TASK *task)
{
    int i, found;
    PostLoLoad(task);
    if (task->job != 0)
        AppendSlEntry(&task->job->sllist, task);
    found = 0;
    for (i = 0; i < task->cprereq; i++) {
        TASK *prereq = PloFindSwObject_thunk(&B_003DD490, 0x105, task->aoidPrereq[i], 0);
        if (prereq != 0)
            task->aprereq[found++] = prereq;
    }
    task->cprereq = found;
    s32 *pathEnter = task->pathEnter;
    s32 *pathComplete = task->pathComplete;
    found = 0;
    for (i = 0; i < task->cdep; i++) {
        TASK *dependent = PloFindSwObject_thunk(&B_003DD490, 0x105, task->aoidDep[i], 0);
        if (dependent != 0)
            task->adep[found++] = dependent;
    }
    task->cdep = found;
    if (!FIsCurrentTask(task) && FTaskRunning(task)) {
        ApplyTaskToggles(task, 5, task->ctoggle, task->atoggle);
        ApplyTaskAnims(task, 5, task->canim, task->aanim, 1);
    }
    if (task->pathEnter[0] != 0) {
        int cEnter = RefGetGameSaveValue(pathEnter, &B_003D4A60).m_tag.m_n;
        task->cEnter = cEnter;
    }
    if (task->pathComplete[0] != 0) {
        int cComplete = RefGetGameSaveValue(pathComplete, &B_003D4A60).m_tag.m_n;
        task->cComplete = cComplete;
    }
    float limit = task->tLimit;
    if (limit == 0.0f && task->ploMarker == 0)
        return;
    if ((((s64)task->grfo << 8) >> 60) == 2)
        func_001A6CA8(task, 0);
    unsigned flags = task->grfSw;
    if ((flags ^ 1) & 1)
        task->pgrfentry->grf |= 2;
    else
        task->grfSw = flags | 2;
}
