#include "sly2.h"
#include "job.h"
struct CRefX { int tagk; int n; int pad[2]; };
struct JOBMGR { u8 unknown_0x0[0x10]; int fieldA; int fieldB; int oid; };
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
extern "C" {
extern SW B_003DD490;
extern const char RO_002A5238[];
void CRef_Destruct(CRefX *);
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void OrderTasks(int *, TASK ***);
TASK *PloFindSwObject_thunk(SW *, int, int, void *);
void RestoreTaskStateFromSave(TASK *);
void SetTaskState(TASK *, int);
void ApplyTaskState(TASK *, int);
void func_001D8B20(CRefX *, CRefX *, const char *, int);
}
extern "C" void func_00165280(JOBMGR *self)
{
    if (!(B_003DD490.loadreq.grf & 8))
        return;
    char frame[0x10];
    int ctask;
    TASK **aptask;
    CStackFrame_Construct(frame);
    OrderTasks(&ctask, &aptask);
    for (int index = 0; index < ctask; index++) {
        TASK *ptask = aptask[index];
        CTaskHold hold(ptask, 3);
        RestoreTaskStateFromSave(ptask);
    }
    TASK *pjob = PloFindSwObject_thunk(&B_003DD490, 0x105, self->oid, 0);
    self->fieldA = pjob->job->oid;
    self->fieldB = pjob->oid;
    {
    CTaskHold holdJob(pjob, 3);
    SetTaskState(pjob, 1);
    int value = pjob->field_0xC0;
    if (value != -1) {
        CRefX result;
        CRefX arg;
        arg.tagk = 0x15;
        arg.n = value;
        func_001D8B20(&result, &arg, RO_002A5238, 0);
        CRef_Destruct(&result);
        CRef_Destruct(&arg);
    }
    for (int index = 0; index < ctask; index++) {
        TASK *ptask = aptask[index];
        CTaskHold hold(ptask, 3);
        ApplyTaskState(ptask, -1);
    }
    B_003DD490.loadreq.field_0x44 = pjob->oidSpawn;
    B_003DD490.loadreq.field_0x48 = -1;
    B_003DD490.loadreq.grf = (B_003DD490.loadreq.grf & ~8) | 4;
    }
    CStackFrame_Destructor(frame, 2);
}
