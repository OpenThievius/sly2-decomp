#include "sly2.h"
#include "clock.h"
#include "job.h"

extern "C" void UpdateLo(TASK *task);
extern "C" void SendTaskTimeLimit(TASK *task, int limit);
extern "C" int B_003E0F9C;

extern "C" void UpdateTask(TASK *task)
{
    UpdateLo(task);
    if (task->state == 1) {
        if (0.0f < task->tLimit) {
            float gap = g_2dded0.t - task->tState;
            if (gap < task->tLimit) {
                if (task->tLimit + g_2dded0.dt <= gap) {
                    SendTaskTimeLimit(task, 0);
                }
            }
        }
    }
    if (task->ploMarker != 0) {
        int chooseFirst = (task->state == 1);
        if (B_003E0F9C != 0) {
            chooseFirst = 0;
        }
        if (chooseFirst) {
            task->ploMarker->Add();
        } else {
            task->ploMarker->Remove();
        }
    }
}
