#include "sly2.h"
#include "job.h"
struct CRefX { int tagk; int n; int pad[2]; };
#include "sw.h"
struct CTaskHold {
    JOB *pother;
    TASK *ptask;
    int saveF4;
    int saveF8;
    CTaskHold(TASK *task, int value)
    {
        pother = 0;
        ptask = task;
        if (ptask != 0) {
            saveF4 = ptask->cause;
            ptask->cause = value;
            saveF8 = ptask->causeArg;
            ptask->causeArg = 0;
        }
    }
    ~CTaskHold()
    {
        if (pother != 0) {
            pother->cause = saveF4;
            pother->causeArg = saveF8;
        }
        if (ptask != 0) {
            ptask->cause = saveF4;
            ptask->causeArg = saveF8;
        }
    }
};
struct CJobHold {
    JOB *pjob;
    TASK *pother;
    int saveF0;
    int saveF4;
    CJobHold(JOB *job, int value)
    {
        pjob = job;
        pother = 0;
        if (pjob != 0) {
            saveF0 = pjob->cause;
            pjob->cause = value;
            saveF4 = pjob->causeArg;
            pjob->causeArg = 0;
        }
    }
    ~CJobHold()
    {
        if (pjob != 0) {
            pjob->cause = saveF0;
            pjob->causeArg = saveF4;
        }
        if (pother != 0) {
            pother->cause = saveF0;
            pother->causeArg = saveF4;
        }
    }
};
extern "C" {
extern SW B_003DD490;
extern const char RO_002A5238[];
void CRef_Destruct(CRefX *);
void EndJob(JOB *);
int IdCurrentLevel(void);
int PdescFromLevelRow(int);
void RequestTransition(SW *, int, int, int, int, int);
void SetCurrentJob(JOB *);
void SetTaskState(TASK *, int);
void SwitchCurrentTask(TASK *);
void func_001D8B20(CRefX *, CRefX *, const char *, int);
void RestartAtTask(TASK *task)
{
    CTaskHold holdTask(task, 2);
    CJobHold holdJob(task->job, 2);
    if (task->job != B_003DD490.pjobCurrent) {
        if (B_003DD490.pjobCurrent != 0) {
            CJobHold holdCur(B_003DD490.pjobCurrent, 2);
            EndJob(B_003DD490.pjobCurrent);
        }
        if (task->job != 0)
            SetCurrentJob(task->job);
    }
    SetTaskState(task, 1);
    SwitchCurrentTask(task);
    int value = task->field_0xC0;
    if (value != -1) {
        CRefX result;
        CRefX arg;
        arg.tagk = 0x15;
        arg.n = value;
        func_001D8B20(&result, &arg, RO_002A5238, 0);
        CRef_Destruct(&result);
        CRef_Destruct(&arg);
    }
    int mode = 4;
    int row = task->oidSpawn == -1 ? 0x189 : task->oidSpawn;
    if (B_003DD490.field_0x3E38 != 0 && (task->levelRow == -1 || task->levelRow == IdCurrentLevel()))
        mode = 0x24;
    RequestTransition(&B_003DD490, PdescFromLevelRow(task->levelRow), row, -1, mode, 0x30A);
}
}
