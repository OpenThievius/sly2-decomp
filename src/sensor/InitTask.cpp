#include "job.h"
#include "sw.h"
extern "C" {
void InitLo();
extern SW B_003DD490;
void InitTask(TASK *task) {
    InitLo();
    task->state = -1;
    task->pending = -1;
    task->cause = 0;
    task->labelId = -1;
    task->oidSpawn = -1;
    task->levelRow = -1;
    task->field_0xC0 = -1;
    B_003DD490.ctask++;
}
}
