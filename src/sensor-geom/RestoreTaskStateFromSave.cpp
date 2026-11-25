#include "sly2.h"
#include "cref.h"
#include "job.h"
extern "C" int B_003D4A60;
extern "C" CRef RefGetGameSaveValue(void *, int *);
extern "C" void ApplyTaskState(TASK *, int);
void RestoreTaskStateFromSave(TASK *task)
{
    int state = 0;
    int forced = 0;
    s32 *pathState = task->pathState;
    if (pathState[0] != 0) {
        int value = RefGetGameSaveValue(pathState, &B_003D4A60).m_tag.m_n;
        state = value;
    }
    s32 *pathForced = task->pathForced;
    if (pathForced[0] != 0) {
        int value = RefGetGameSaveValue(pathForced, &B_003D4A60).m_tag.m_n;
        forced = value;
    }
    if (forced != 0 && task->job != 0 && state < 3 && 0 < state) {
        task->cEnter = 0;
        state = 1;
        if (task->job->ptaskStart == task)
            task->job->count = 0;
        for (int index = 0; index < task->cprereq; index++) {
            if (task->aprereq[index]->state <= 1) {
                state = 0;
                break;
            }
        }
    }
    if (state == 0)
        state = task->cprereq == 0;
    ApplyTaskState(task, state);
}
