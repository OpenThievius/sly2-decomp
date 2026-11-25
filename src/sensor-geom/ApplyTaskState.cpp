#include "clock.h"
#include "dl.h"
#include "job.h"
extern "C" {
void AppendDlEntry(DL *, TASK *);
void ApplyTaskAnims(TASK *, int, int, ANIMREC *, int);
void ApplyTaskToggles(TASK *, int, int, void *);
int FTaskRunning(TASK *);
void LeaveTaskIfCurrent(TASK *);
void RemoveDlEntry(DL *, TASK *);
void SaveTaskVariables(TASK *);
void SwitchCurrentTask(TASK *);
void bevy_camera_follow_activity(void *, int, TASK *);
extern char B_002DEB30[];
extern int B_002DEB44;
extern DL B_003E0F90;
void ApplyTaskState(TASK *task, int newState) {
    if (task->state != newState) {
        if (FTaskRunning(task) != 0) {
            bevy_camera_follow_activity(B_002DEB30, 0x26, task);
            task->HandleSpliceEvent(0x16, 0, 0, 0, 0);
        }
        if (task->state == 1) RemoveDlEntry(&B_003E0F90, task);
        if (FTaskRunning(task) != 0) {
            ApplyTaskToggles(task, newState, task->ctoggle, task->atoggle);
            ApplyTaskAnims(task, newState, task->canim, task->aanim, task->cause);
        }
        switch (newState) {
        case 0:
            if (task->cause == 4) {
                JOB *owner = task->job;
                task->cEnter = 0;
                task->cComplete = 0;
                if (owner != 0) {
                    if (owner->ptaskStart == task) owner->count = 0;
                }
            }
            break;
        case 1:
            AppendDlEntry(&B_003E0F90, task);
            break;
        case 2:
            if (task->cause == 0) task->cComplete = task->cComplete + 1;
            break;
        }
        task->state = newState;
        task->tState = g_2dded0.t;
        SaveTaskVariables(task);
        if (FTaskRunning(task) != 0) {
            bevy_camera_follow_activity(B_002DEB30, 0x25, task);
            task->HandleSpliceEvent(0x15, 0, 0, 0, 0);
            task->PostMessage(0x11, task);
        }
        unsigned kind = task->cause;
        switch (kind) {
        case 1:
            if (task->state == 1 && task->field_0x74 != 0) {
                B_002DEB44 = task->oid;
                return;
            }
            break;
        case 3:
            break;
        case 0:
        case 2:
        case 4:
            int stateNow = task->state;
            switch (stateNow) {
            case 1:
                if (task->field_0x70 != 0) {
                    SwitchCurrentTask(task);
                    return;
                }
                break;
            case 0:
            case 3:
                LeaveTaskIfCurrent(task);
                break;
            }
            break;
        }
    }
}
}
