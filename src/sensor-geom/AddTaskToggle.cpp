#include "job.h"
struct TASKTOGGLE { int word0; int word4; int word8; int wordC; };
extern "C" {
int func_00162050(int);
void AddTaskToggle(TASK *task, int arg1, int arg2, int arg3, int arg4) {
    if (task->field_0x50 == 0) {
        int index = task->ctoggle;
        if (index < 0x20) {
            TASKTOGGLE *toggle = (TASKTOGGLE *)task->atoggle + index;
            task->ctoggle = index + 1;
            toggle->word0 = arg1;
            toggle->word4 = arg3;
            toggle->word8 = func_00162050(arg2);
            toggle->wordC = arg4;
        }
    }
}
}
